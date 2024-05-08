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
#include "env.h"
#include "utils.h"
#include "WifiFunctions.h"
#include "FlapFunctions.h"

unsigned long previousMillis = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

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
          writeThroughAlignment(p->value());
#ifdef serial
          Serial.print("Alignment set to: ");
          Serial.println(getAlignment());
#endif
        }

        // HTTP POST speed slider value
        if (p->name() == PARAM_SPEEDSLIDER) {
          writeThroughSpeedSlider(p->value());
#ifdef serial
          Serial.print("Speed set to: ");
          Serial.println(getSpeedSlider());
#endif
        }

        // HTTP POST mode value
        if (p->name() == PARAM_DEVICEMODE) {
          writeThroughDeviceMode(p->value());
#ifdef serial
          Serial.print("Mode set to: ");
          Serial.println(getDeviceMode());
#endif
        }

        // HTTP POST input1 value
        if (p->name() == PARAM_INPUT_1) {
          setInput1(p->value());
#ifdef serial
          Serial.print("Input 1 set to: ");
          Serial.println(getInput1());
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
    String deviceMode = getDeviceMode();
    if (deviceMode == "text") {
      showNewData(getInput1());
    } else if (deviceMode == "date") {
      showDate();
    } else if (deviceMode == "clock") {
      showClock();
    }
  }

}
