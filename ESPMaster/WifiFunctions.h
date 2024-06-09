// WifiFunctions.h

#ifndef WIFIFUNCTIONS_H
#define WIFIFUNCTIONS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

void writeThroughAlignment(String message);
void writeThroughSpeedSlider(String message);
void writeThroughDeviceMode(String message);
void setText(String message);
void setOffsetUpdateUnitAddr(int unitAddr);
void setOffsetUpdateOffset(int offset);
String getAlignment();
String getDeviceMode();
String getText();
String getSpeedSlider();
String getWrittenLast();
int getOffsetUpdateUnitAddr();
int getOffsetUpdateOffset();
void setWrittenLast(String message);
void loadFSValues();
String getCurrentInputValues();
IPAddress initWiFi();
void initFS();

#endif // WIFIFUNCTIONS_H