#include <Arduino.h>

void debugF(const char* format, ...) {
    #ifdef serial
        Serial.printf(format);
    #endif
}