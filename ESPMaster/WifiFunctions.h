// WifiFunctions.h

#ifndef WIFIFUNCTIONS_H
#define WIFIFUNCTIONS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

String readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void writeThroughAlignment(String message);
void writeThroughSpeedSlider(String message);
void writeThroughDeviceMode(String message);
void setInput1(String message);
String getAlignment();
String getDeviceMode();
String getInput1();
String getSpeedSlider();
String getWrittenLast();
void setWrittenLast(String message);
void loadFSValues();
String getCurrentInputValues();
void initWiFi();
void initFS();

#endif // WIFIFUNCTIONS_H