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

bool offsetUpdateFlag = false;
unsigned long previousFlapMillis = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

Timezone timezone; // create ezTime timezone object

void setup()
{
  // Serial port for debugging purposes
#ifdef serial
  Serial.begin(BAUDRATE);
  Serial.println("master start");
#endif

  Wire.begin(4, 5); // For ESP12-F

  IPAddress ip = initWiFi(); // initializes WiFi
  initFS();                  // initializes filesystem
  loadFSValues();            // loads initial values from filesystem

  // ezTime initialization
  waitForSync();
  timezone.setLocation(TIMEZONE_STRING);

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    debugF("Root URL\n");
    request->send(LittleFS, "/index.html", "text/html"); });
  debugF("Registered the root path\n");

  server.serveStatic("/", LittleFS, "/");

  server.on("/values", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String json = getCurrentInputValues();
    request->send(200, "application/json", json);
    json = String(); });

  server.on("/offset", HTTP_POST, [](AsyncWebServerRequest *request)
            {
    debugF("/offset POST request\n");
    int params = request->params();
    int unitAddr = -1;
    int offset = -1;
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      if (p->isPost()) {
        if (p->name() == PARAM_OFFSET_UNIT_ADDR) {
          String unitAddrStr = p->value();
          unitAddr = unitAddrStr.toInt();
        }
        if (p->name() == PARAM_OFFSET_OFFSET) {
          String offsetStr = p->value();
          offset = offsetStr.toInt();
        }
      }
    }
    if (unitAddr != -1 && offset != -1) {
        setOffsetUpdateUnitAddr(unitAddr);
        setOffsetUpdateOffset(offset);
        offsetUpdateFlag = true;
    } else {
      Serial.println("Invalid offset or unit address");
      Serial.print("Unit address: ");
      Serial.println(unitAddr);
      Serial.print("Offset: ");
      Serial.println(offset);
    }
    request->send(LittleFS, "/index.html", "text/html"); });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request)
            {
    debugF("POST request\n");
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
    request->send(LittleFS, "/index.html", "text/html"); });
  server.begin();
  debugF("master ready\n");
  showMessage(ip.toString(), 12);
}

void loop()
{
  events(); // ezTime library function

  // Reset loop delay
  unsigned long currentMillis = millis();

  // Delay to not spam web requests
  if (currentMillis - previousFlapMillis >= 1024)
  {
    previousFlapMillis = currentMillis;

    if (offsetUpdateFlag)
    {
      offsetUpdateFlag = false;
      // Make sure that the display is on the home position
      writeThroughDeviceMode("text");
      setInput1(" ");
      updateOffset(false);
    }

    // Mode Selection
    String deviceMode = getDeviceMode();
    Serial.print("Loop. Device Mode: ");
    Serial.println(deviceMode);
    if (deviceMode == "text")
    {
      showNewData(getInput1());
    }
    else if (deviceMode == "date")
    {
      showDate();
    }
    else if (deviceMode == "clock")
    {
      showClock();
    }
  }
}
