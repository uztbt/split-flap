#include <Arduino_Json.h>
#include "WifiFunctions.h"
#include "LittleFS.h"
#include "env.h"
#include "files.h"

JSONVar values;
// Variables to save values from HTML form
String writtenLast;
String alignment;
String speedslider;
String devicemode;
String input1;

void writeThroughAlignment(String message)
{
  alignment = message;
  writeFile(LittleFS, ALIGNMENT_PATH, alignment.c_str());
}

void writeThroughSpeedSlider(String message)
{
  speedslider = message;
  writeFile(LittleFS, SPEEDSLIDER_PATH, speedslider.c_str());
}

void writeThroughDeviceMode(String message)
{
  devicemode = message;
  writeFile(LittleFS, DEVICEMODE_PATH, devicemode.c_str());
}

void setInput1(String message)
{
  input1 = message;
}

String getAlignment()
{
  return alignment;
}

String getDeviceMode()
{
  return devicemode;
}

String getInput1()
{
  return input1;
}

String getSpeedSlider()
{
  return speedslider;
}

String getWrittenLast()
{
  return writtenLast;
}

void setWrittenLast(String message)
{
  writtenLast = message;
}

void loadFSValues()
{
  // Load values saved in LittleFS
  alignment = readFile(LittleFS, ALIGNMENT_PATH);
  speedslider = readFile(LittleFS, SPEEDSLIDER_PATH);
  devicemode = readFile(LittleFS, DEVICEMODE_PATH);
}

String getCurrentInputValues()
{
  values["alignment"] = alignment;
  values["speedSlider"] = speedslider;
  values["devicemode"] = devicemode;

  String jsonString = JSON.stringify(values);
  return jsonString;
}

// Initialize WiFi
IPAddress initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.hostname("SplitFlap");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#ifdef serial
  Serial.print("Connecting to WiFi ..");
#endif
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
#ifdef serial
  Serial.println(WiFi.localIP());
#endif
  return WiFi.localIP();
}
