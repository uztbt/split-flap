#include <Arduino.h>
#include <Wire.h>
#include <Stepper.h>
#include <EEPROM.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include "env.h"

unsigned long lastRotation = 0;

// globals
int displayedLetter = 0; // currently shown letter
int desiredLetter = 0;   // letter to be shown
const String letters[] = {" ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Ä", "Ö", "Ü", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ".", "-", "?", "!"};
Stepper stepper(STEPS, STEPPERPIN1, STEPPERPIN3, STEPPERPIN2, STEPPERPIN4); // stepper setup
bool lastInd1 = false;                                                      // store last status of phase
bool lastInd2 = false;                                                      // store last status of phase
bool lastInd3 = false;                                                      // store last status of phase
bool lastInd4 = false;                                                      // store last status of phase
float missedSteps = 0;                                                      // cummulate steps <1, to compensate via additional step when reaching >1
int currentlyrotating = 0;                                                  // 1 = drum is currently rotating, 0 = drum is standing still
int stepperSpeed = 10;                                                      // current speed of stepper, value only for first homing
int calOffset;                                                              // Offset for calibration in steps, stored in EEPROM, gets read in setup
int letterNumber = 0;
int i2cAddress;
bool offsetUpdatedFlag = false;

// sleep globals
const unsigned long WAIT_TIME = 2000; // wait time before sleep routine gets executed again in milliseconds
unsigned long previousMillis = 0;     // stores last time sleep was interrupted

// setup
void setup()
{
  // i2c adress switch
  pinMode(ADRESSSW1, INPUT_PULLUP);
  pinMode(ADRESSSW2, INPUT_PULLUP);
  pinMode(ADRESSSW3, INPUT_PULLUP);
  pinMode(ADRESSSW4, INPUT_PULLUP);

  // hall sensor
  pinMode(HALLPIN, INPUT);

  i2cAddress = getaddress(); // get I2C Address and save in variable

  // initialize serial
  Serial.begin(BAUDRATE);
  Serial.println("starting unit");
  Serial.print("I2CAddress: ");
  Serial.println(i2cAddress);

  uint8_t restartTimes = EEPROM.read(0);
  EEPROM.write(0, restartTimes + 1);

  // I2C function assignment
  Wire.begin(i2cAddress);         // i2c address of this unit
  Wire.onReceive(commandHandler); // call-function for transfered letter via i2c
  Wire.onRequest(requestEvent);   // call-funtion if master requests unit state

  getOffset();     // get calibration offset
  calibrate(true); // home stepper after startup

// test calibration settings
#ifdef test
  int calLetters[10] = {0, 26, 1, 21, 14, 43, 30, 31, 32, 39};
  for (int i = 0; i < 10; i++)
  {
    int currentCalLetter = calLetters[i];
    rotateToLetter(currentCalLetter);
    delay(2000);
  }
#endif
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= WAIT_TIME)
  {
    byte old_ADCSRA = ADCSRA;
    // disable ADC
    ADCSRA = 0;
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
#ifdef serial
    digitalWrite(LED_BUILTIN, LOW); // shuts off LED when starting to sleep, for debugging
#endif
    sleep_cpu();
#ifdef serial
    digitalWrite(LED_BUILTIN, HIGH); // turns on LED when waking up, for debugging
#endif
    sleep_disable();
    previousMillis = currentMillis; // reset sleep counter
    ADCSRA = old_ADCSRA;

    // release TWI bus
    TWCR = bit(TWEN) | bit(TWIE) | bit(TWEA) | bit(TWINT);

    // turn it back on again
    Wire.begin(i2cAddress);
  } // end of time to sleep

  if (offsetUpdatedFlag)
  {
    offsetUpdatedFlag = false;
    calibrate(true);
  }

  // check if new letter was received through i2c
  if (displayedLetter != letterNumber)
  {
#ifdef serial
    Serial.print("Value over serial received: ");
    Serial.print(letterNumber);
    Serial.print(" Letter: ");
    Serial.print(letters[letterNumber]);
    Serial.println();
#endif
    // rotate to new letter
    rotateToLetter(letterNumber);
  }
}

// rotate to letter
void rotateToLetter(int toLetter)
{
  if (lastRotation == 0 || (millis() - lastRotation > OVERHEATINGTIMEOUT * 1000))
  {
    lastRotation = millis();
    // get letter position
    int posLetter = -1;
    posLetter = toLetter;
    int posCurrentLetter = -1;
    posCurrentLetter = displayedLetter;
    // int amountLetters = sizeof(letters) / sizeof(String);
#ifdef serial
    Serial.print("go to letter: ");
    Serial.println(letters[toLetter]);
#endif
    // go to letter, but only if available (>-1)
    if (posLetter > -1)
    { // check if letter exists
      // check if letter is on higher index, then no full rotaion is needed
      if (posLetter >= posCurrentLetter)
      {
#ifdef serial
        Serial.println("direct");
#endif
        // go directly to next letter, get steps from current letter to target letter
        int diffPosition = posLetter - posCurrentLetter;
        startMotor();
        stepper.setSpeed(stepperSpeed);
        // doing the rotation letterwise
        for (int i = 0; i < diffPosition; i++)
        {
          float preciseStep = (float)STEPS / (float)NUM_FLAPS;
          int roundedStep = (int)preciseStep;
          missedSteps = missedSteps + ((float)preciseStep - (float)roundedStep);
          if (missedSteps > 1)
          {
            roundedStep = roundedStep + 1;
            missedSteps--;
          }
          stepper.step(ROTATIONDIRECTION * roundedStep);
        }
      }
      else
      {
        // full rotation is needed, good time for a calibration
#ifdef serial
        Serial.println("full rotation incl. calibration");
#endif
        calibrate(false); // calibrate revolver and do not stop motor
        // startMotor();
        stepper.setSpeed(stepperSpeed);
        for (int i = 0; i < posLetter; i++)
        {
          float preciseStep = (float)STEPS / (float)NUM_FLAPS;
          int roundedStep = (int)preciseStep;
          missedSteps = missedSteps + (float)preciseStep - (float)roundedStep;
          if (missedSteps > 1)
          {
            roundedStep = roundedStep + 1;
            missedSteps--;
          }
          stepper.step(ROTATIONDIRECTION * roundedStep);
        }
      }
      // store new position
      displayedLetter = toLetter;
      // rotation is done, stop the motor
      delay(100); // important to stop rotation before shutting of the motor to avoid rotation after switching off current
      stopMotor();
    }
    else
    {
#ifdef serial
      Serial.println("letter unknown, go to space");
#endif
      desiredLetter = 0;
    }
  }
}

void commandHandler(int numBytes)
{
  int receivedInts[3];

  for (int i = 0; i < numBytes; i++)
  {
    Serial.print("Received byte ");
    Serial.print(i);
    Serial.print(": ");
    receivedInts[i] = Wire.read();
    Serial.println(receivedInts[i]);
  }
  // Write received bytes to correct variables
  int kind = receivedInts[0];

  Serial.print("Command received: ");
  Serial.println(kind);
  Serial.print("COMMAND_UPDATE_OFFSET: ");
  Serial.println(COMMAND_UPDATE_OFFSET);
  Serial.print("COMMAND_SHOW_LETTER: ");
  Serial.println(COMMAND_SHOW_LETTER);

  if (kind == COMMAND_UPDATE_OFFSET)
  {
    int newOffset = receivedInts[EEPROM_ADDR_OFFSET_HIGHER_BYTE] << 8 | receivedInts[EEPROM_ADDR_OFFSET_LOWER_BYTE];
    if (newOffset != calOffset)
    {
      calOffset = newOffset;
      EEPROM.write(EEPROM_ADDR_OFFSET_HIGHER_BYTE, receivedInts[EEPROM_ADDR_OFFSET_HIGHER_BYTE]);
      EEPROM.write(EEPROM_ADDR_OFFSET_LOWER_BYTE, receivedInts[EEPROM_ADDR_OFFSET_LOWER_BYTE]);
      Serial.print("Caloffset updated: ");
      Serial.println(calOffset);
      offsetUpdatedFlag = true;
    }
    else
    {
      Serial.print("Caloffset not updated because it is the same as before: ");
      Serial.println(calOffset);
    }
  }
  else if (kind == COMMAND_SHOW_LETTER)
  {
    Serial.print("Letter received: ");
    letterNumber = receivedInts[1];
    stepperSpeed = receivedInts[2];
    Serial.print(letters[letterNumber]);
    Serial.print(" Speed: ");
    Serial.println(stepperSpeed);
  }
  else
  {
    Serial.println("Unknown command");
  }
}

void requestEvent()
{
  // Send unit status to master
  Wire.write(currentlyrotating);
  // Send offset to master
  Wire.write(EEPROM.read(EEPROM_ADDR_OFFSET_HIGHER_BYTE));
  Wire.write(EEPROM.read(EEPROM_ADDR_OFFSET_LOWER_BYTE));
  Serial.print("Offset sent: ");
  Serial.print(EEPROM.read(EEPROM_ADDR_OFFSET_HIGHER_BYTE));
  Serial.print(" ");
  Serial.println(EEPROM.read(EEPROM_ADDR_OFFSET_LOWER_BYTE));
  /*
    #ifdef serial
    Serial.print("Status ");
    Serial.print(currentlyrotating);
    Serial.print(" sent to master");
    Serial.println();
    #endif
  */
}

// returns the adress of the unit as int from 0-15
int getaddress()
{
  int address = !digitalRead(ADRESSSW4) + (!digitalRead(ADRESSSW3) * 2) + (!digitalRead(ADRESSSW2) * 4) + (!digitalRead(ADRESSSW1) * 8);
  return address;
}

// gets magnet sensor offset from EEPROM in steps
void getOffset()
{
  int highByte = EEPROM.read(EEPROM_ADDR_OFFSET_HIGHER_BYTE);
  int lowByte = EEPROM.read(EEPROM_ADDR_OFFSET_LOWER_BYTE);
  calOffset = highByte << 8 | lowByte;
  Serial.print("Caloffset: ");
  Serial.println(calOffset);
}

// doing a calibration of the revolver using the hall sensor
int calibrate(bool initialCalibration)
{
#ifdef serial
  Serial.println("calibrate revolver");
#endif
  currentlyrotating = 1; // set active state to active
  bool reachedMarker = false;
  stepper.setSpeed(stepperSpeed);
  int i = 0;
  while (!reachedMarker)
  {
    // Because of the different wiring of the hall sensors
    int currentHallValue = i2cAddress < 9 ? digitalRead(HALLPIN) : !digitalRead(HALLPIN);
    Serial.print("Hall: ");
    Serial.println(currentHallValue);

    if (currentHallValue == 1 && i == 0)
    { // already in zero position move out a bit and do the calibration {
      // not reached yet
      i = 50;
      stepper.step(ROTATIONDIRECTION * 50); // move 50 steps to get out of scope of hall
    }
    else if (currentHallValue == 1)
    {
      // not reached yet
      stepper.step(ROTATIONDIRECTION * 3);
    }
    else
    {
      // reached marker, go to calibrated offset position
      reachedMarker = true;
      stepper.step(ROTATIONDIRECTION * calOffset);
      displayedLetter = 0;
      missedSteps = 0;
#ifdef serial
      Serial.println("revolver calibrated");
#endif
      // Only stop motor for initial calibration
      if (initialCalibration)
      {
        stopMotor();
      }
      return i;
    }
    if (i > 3 * STEPS)
    {
      // seems that there is a problem with the marker or the sensor. turn of the motor to avoid overheating.
      displayedLetter = 0;
      desiredLetter = 0;
      reachedMarker = true;
#ifdef serial
      Serial.println("calibration revolver failed");
#endif
      stopMotor();
      return -1;
    }
    i++;
  }
  return i;
}

// switching off the motor driver
void stopMotor()
{
  lastInd1 = digitalRead(STEPPERPIN1);
  lastInd2 = digitalRead(STEPPERPIN2);
  lastInd3 = digitalRead(STEPPERPIN3);
  lastInd4 = digitalRead(STEPPERPIN4);

  digitalWrite(STEPPERPIN1, LOW);
  digitalWrite(STEPPERPIN2, LOW);
  digitalWrite(STEPPERPIN3, LOW);
  digitalWrite(STEPPERPIN4, LOW);
#ifdef serial
  Serial.println("Motor Stop");
#endif
  currentlyrotating = 0; // set active state to not active
  delay(100);
}

void startMotor()
{
#ifdef serial
  Serial.println("Motor Start");
#endif
  currentlyrotating = 1; // set active state to active
  digitalWrite(STEPPERPIN1, lastInd1);
  digitalWrite(STEPPERPIN2, lastInd2);
  digitalWrite(STEPPERPIN3, lastInd3);
  digitalWrite(STEPPERPIN4, lastInd4);
}
