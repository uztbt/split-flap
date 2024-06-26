#pragma once

#ifndef BAUDRATE
#define BAUDRATE 9600
#endif

#ifndef NUM_FLAPS
#define NUM_FLAPS 45
#endif

// Pins of I2C adress switch
// https://europe1.discourse-cdn.com/arduino/original/4X/7/b/2/7b223c07c6657f87fe374782fdd86f353b475f1a.jpeg
#define ADRESSSW1 6 // PD 6
#define ADRESSSW2 5 // PD 5
#define ADRESSSW3 4 // PD 4
#define ADRESSSW4 3 // PD 3

//constants stepper
#define STEPPERPIN1 11
#define STEPPERPIN2 10
#define STEPPERPIN3 9
#define STEPPERPIN4 8
#define STEPS 2038 //28BYJ-48 stepper, number of steps
#define HALLPIN 7 //Pin of hall sensor

//constants others
#define ROTATIONDIRECTION 1 //-1 for reverse direction
#define OVERHEATINGTIMEOUT 2 //timeout in seconds to avoid overheating of stepper. After starting rotation, the counter will start. Stepper won't move again until timeout is passed
#define COMMAND_UPDATE_OFFSET 0 //command to update offset
#define COMMAND_SHOW_LETTER 1 //command to show letter

// EEPROM addresses
#define EEPROM_ADDR_OFFSET_HIGHER_BYTE 1 //offset in EEPROM
#define EEPROM_ADDR_OFFSET_LOWER_BYTE 2 //offset in EEPROM

// 2038 steps / 45 letters = 45.28888 steps / letter
#define OFFSET_0 1155 // 25 letters * 45.28888 steps / letter = 1132 steps, plus x
#define OFFSET_1 1375 // O: 30 letters * 45.28888 steps / letter = 1358 steps, plus x
#define OFFSET_2 1615 // J: 35 letters * 45.28888 steps / letter = 1585 steps, plus x
#define OFFSET_3 1912 // C: 42 letters * 45.28888 steps / letter = 1902 steps, plus x
#define OFFSET_4 2012 // A: 44 letters * 45.28888 steps / letter = 1992 steps, plus x
#define OFFSET_5 780 // &: 17 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_6 780 // &: 17 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_7 780 // &: 17 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_8 755 // # 16 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_9 825 // $: 18 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_10 725 // #: 16 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_11 735 // #: 16 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_12 725 // #: 16 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_13 770 // &: 17 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_14 770 // &: 17 letters * 45.28888 steps / letter = 770 steps, plus x
#define OFFSET_15 725 // &: 16 letters * 45.28888 steps / letter = 770 steps, plus x
