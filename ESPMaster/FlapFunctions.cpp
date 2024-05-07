#include <Wire.h>
#include <ezTime.h>
#include "FlapFunctions.h"
#include "env.h"
#include "WifiFunctions.h"

int displayState[UNITSAMOUNT];
const char letters[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '$', '&', '#', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', '.', '-', '?', '!'};

//translates char to letter position
int translateLettertoInt(char letterchar) {
  for (int i = 0; i < FLAPAMOUNT; i++) {
    if (letterchar == letters[i]) {
      return i;
    }
  }
  return -1;
}

//checks for new message to show
void showNewData(String message) {
  if (getWrittenLast() != message) {
    showMessage(message, convertSpeed(getSpeedSlider()));
  }
  setWrittenLast(message);
}

//write letter position and speed in rpm to single unit
void writeToUnit(int address, int letter, int flapSpeed) {
  int sendArray[2] = {letter, flapSpeed}; //Array with values to send to unit

  Wire.beginTransmission(address);

  //Write values to send to slave in buffer
  for (unsigned int i = 0; i < sizeof sendArray / sizeof sendArray[0]; i++) {
#ifdef serial
    Serial.print("sendArray: ");
    Serial.println(sendArray[i]);
#endif
    Wire.write(sendArray[i]);
  }
  Wire.endTransmission(); //send values to unit
}


//pushes message to units
void showMessage(String message, int flapSpeed) {

  //Format string per alignment choice
  String alignment = getAlignment();
  if (alignment == "left") {
    message = leftString(message);
  } else if (alignment == "right") {
    message = rightString(message);
  } else if (alignment == "center") {
    message = centerString(message);
  }

  // wait while display is still moving
  while (isDisplayMoving()) {
#ifdef serial
    Serial.println("wait for display to stop");
#endif
    delay(500);
  }

  Serial.println(message);
  for (int i = 0; i < UNITSAMOUNT; i++) {
    char currentLetter = message[i];
    int currentLetterPosition = translateLettertoInt(currentLetter);
#ifdef serial
    Serial.print("Unit Nr.: ");
    Serial.print(i);
    Serial.print(" Letter: ");
    Serial.print(message[i]);
    Serial.print(" Letter position: ");
    Serial.println(currentLetterPosition);
#endif
    //only write to unit if char exists in letter array
    if (currentLetterPosition != -1) {
      writeToUnit(i, currentLetterPosition, flapSpeed);
    }
  }
}

void showDate() {
  showNewData(dateTime(DATE_FORMAT));
}

void showClock() {
  showNewData(dateTime(CLOCK_FORMAT));
}

//checks if single unit is moving
int checkIfMoving(int address) {
  int active;
  Wire.requestFrom(address, ANSWERSIZE, 1);
  active = Wire.read();
#ifdef serial
  Serial.print(address);
  Serial.print(":");
  Serial.print(active);
  Serial.println();
#endif
  if (active == -1) {
#ifdef serial
    Serial.println("Try to wake up unit");
#endif
    Wire.beginTransmission(address);
    Wire.endTransmission();
    //delay(5);
  }
  return active;
}

//checks if unit in display is currently moving
bool isDisplayMoving() {
  //Request all units moving state and write to array
  for (int i = 0; i < UNITSAMOUNT; i++) {
    displayState[i] = checkIfMoving(i);
    if (displayState[i] == 1) {
#ifdef serial
      Serial.println("A unit in the display is busy");
#endif
      return true;

      //if unit is not available through i2c
    } else if (displayState[i] == -1) {
#ifdef serial
      Serial.println("A unit in the display is sleeping");
#endif
      return true;
    }
  }
#ifdef serial
  Serial.println("Display is standing still");
#endif
  return false;
}
