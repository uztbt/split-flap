#include <Arduino_Json.h>
#include "WifiFunctions.h"
#include "LittleFS.h"
#include "env.h"

JSONVar values;
//Variables to save values from HTML form
String writtenLast;
String alignment;
String speedslider;
String devicemode;
String input1;

// File paths to save input values permanently
const char* alignmentPath = "/alignment.txt";
const char* speedsliderPath = "/speedslider.txt";
const char* devicemodePath = "/devicemode.txt";

// Read File from LittleFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return String();
  }

  String fileContent;
  while (file.available()) {
    fileContent = file.readStringUntil('\n');
    break;
  }
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, "w");
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}

void writeThroughAlignment(String message) {
  alignment = message;
  writeFile(LittleFS, alignmentPath, alignment.c_str());
}

void writeThroughSpeedSlider(String message) {
  speedslider = message;
  writeFile(LittleFS, speedsliderPath, speedslider.c_str());
}

void writeThroughDeviceMode(String message) {
  devicemode = message;
  writeFile(LittleFS, devicemodePath, devicemode.c_str());
}

void setInput1(String message) {
  input1 = message;
}

String getAlignment() {
  return alignment;
}

String getDeviceMode() {
  return devicemode;
}

String getInput1() {
  return input1;
}

String getSpeedSlider() {
  return speedslider;
}

String getWrittenLast() {
  return writtenLast;
}

void setWrittenLast(String message) {
  writtenLast = message;
}

void loadFSValues() {
  // Load values saved in LittleFS
  alignment = readFile(LittleFS, alignmentPath);
  speedslider = readFile(LittleFS, speedsliderPath);
  devicemode = readFile(LittleFS, devicemodePath);
}

String getCurrentInputValues() {
  values["alignment"] = alignment;
  values["speedSlider"] = speedslider;
  values["devicemode"] = devicemode;

  String jsonString = JSON.stringify(values);
  return jsonString;
}


// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname("SplitFlap");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#ifdef serial
  Serial.print("Connecting to WiFi ..");
#endif
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
#ifdef serial
  Serial.println(WiFi.localIP());
#endif
}


// Initialize LittleFS
void initFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

