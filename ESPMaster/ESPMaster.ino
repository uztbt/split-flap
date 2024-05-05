/*********
  Split Flap ESP Master
*********/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ezTime.h>

const char letters[] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '$', '&', '#', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', '.', '-', '?', '!'};
int displayState[UNITSAMOUNT];
String writtenLast;
unsigned long previousMillis = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_ALIGNMENT = "alignment";
const char* PARAM_SPEEDSLIDER = "speedslider";
const char* PARAM_DEVICEMODE = "devicemode";
const char* PARAM_INPUT_1 = "input1";

//Variables to save values from HTML form
String alignment;
String speedslider;
String devicemode;
String input1;

// File paths to save input values permanently
const char* alignmentPath = "/alignment.txt";
const char* speedsliderPath = "/speedslider.txt";
const char* devicemodePath = "/devicemode.txt";

// TODO: move to WifiFunctions.ino
JSONVar values;

Timezone timezone; //create ezTime timezone object


void setup() {
  // Serial port for debugging purposes
#ifdef serial
  Serial.begin(BAUDRATE);
  Serial.println("master start");
#endif

  //deactivate I2C if debugging the ESP, otherwise serial does not work
#ifndef serial
  Wire.begin(1, 3); //For ESP01 only
#endif
  //Wire.begin(D1, D2); //For NodeMCU testing only SDA=D1 and SCL=D2

  initWiFi(); //initializes WiFi
  initFS(); //initializes filesystem
  loadFSValues(); //loads initial values from filesystem

  //ezTime initialization
  waitForSync();
  timezone.setLocation(TIMEZONE_STRING);

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    debugF("Root URL\n");
    request->send(LittleFS, "/index.html", "text/html");
  });
  debugF("Registered the root path\n");

  server.serveStatic("/", LittleFS, "/");

  server.on("/values", HTTP_GET, [](AsyncWebServerRequest * request) {
    String json = getCurrentInputValues();
    request->send(200, "application/json", json);
    json = String();
  });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest * request) {
    int params = request->params();
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      if (p->isPost()) {

        // HTTP POST alignment value
        if (p->name() == PARAM_ALIGNMENT) {
          alignment = p->value().c_str();
#ifdef serial
          Serial.print("Alignment set to: ");
          Serial.println(alignment);
#endif
          writeFile(LittleFS, alignmentPath, alignment.c_str());
        }

        // HTTP POST speed slider value
        if (p->name() == PARAM_SPEEDSLIDER) {
          speedslider = p->value().c_str();
#ifdef serial
          Serial.print("Speed set to: ");
          Serial.println(speedslider);
#endif
          writeFile(LittleFS, speedsliderPath, speedslider.c_str());
        }

        // HTTP POST mode value
        if (p->name() == PARAM_DEVICEMODE) {
          devicemode = p->value().c_str();
#ifdef serial
          Serial.print("Mode set to: ");
          Serial.println(devicemode);
#endif
          writeFile(LittleFS, devicemodePath, devicemode.c_str());
        }

        // HTTP POST input1 value
        if (p->name() == PARAM_INPUT_1) {
          input1 = p->value().c_str();
#ifdef serial
          Serial.print("Input 1 set to: ");
          Serial.println(input1);
#endif
        }
      }
    }
    request->send(LittleFS, "/index.html", "text/html");
  });
  server.begin();
#ifdef serial
  Serial.println("master ready");
#endif
}


void loop() {

  events(); //ezTime library function

  //Reset loop delay
  unsigned long currentMillis = millis();

  //Delay to not spam web requests
  if (currentMillis - previousMillis >= 1024) {
    previousMillis = currentMillis;

    //Mode Selection
    if (devicemode == "text") {
      showNewData(input1);
    } else if (devicemode == "date") {
      showDate();
    } else if (devicemode == "clock") {
      showClock();
    }
  }

}
