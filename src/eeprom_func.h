#include "EEPROM.h"

// Max size of SSID and PASS is 64 bytes, respectively
// TODO: at least COLOR_SPEED and EFFECT_SPEED are limited to 100, can be
// stored in 1 byte. BRIGHT is limited to 255, can be 1 byte too. PRGM,
// COLOR_MODE, EFFECT probably never will exceed 255, can be 1 byte too.
#define EEPROM_SSID 0
#define EEPROM_PASS 32
#define EEPROM_PRGM 64
#define EEPROM_EFFECT 68
#define EEPROM_BRIGHT 72
#define EEPROM_EFFECT_SPEED 76
#define EEPROM_COLOR_MODE 80
#define EEPROM_R 84
#define EEPROM_G 85
#define EEPROM_B 86
#define EEPROM_COLOR_SPEED 87

#ifndef EEPROM_FUNC_H
#define EEPROM_FUNC_H

bool init_EEPROM();
String eeprom_readString(int address);
void eeprom_writeString(int address, String input);

int eeprom_readInt(int address);
void eeprom_writeInt(int address, int input);

uint8_t eeprom_readByte(int address);
void eeprom_writeByte(int address, uint8_t input);

float eeprom_readFloat(int address);
void eeprom_writeFloat(int address, float input);

#endif