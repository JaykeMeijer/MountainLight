#include "EEPROM.h"

// Max size of SSID and PASS is 64 bytes, respectively
#define EEPROM_SSID 0
#define EEPROM_PASS 32
#define EEPROM_PRGM 64

#ifndef EEPROM_FUNC_H
#define EEPROM_FUNC_H

bool init_EEPROM();
String eeprom_readString(int address);
void eeprom_writeString(int address, String input);

int eeprom_readInt(int address);
void eeprom_writeInt(int address, int input);

#endif