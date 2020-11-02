#include "eeprom_func.h"


bool init_EEPROM() {
    return EEPROM.begin(128);
}

String eeprom_readString(int address) {
    return EEPROM.readString(address);
}

void eeprom_writeString(int address, String input) {
    EEPROM.writeString(address, input);
    EEPROM.commit();
}

int eeprom_readInt(int address) {
    return EEPROM.readInt(address);
}

void eeprom_writeInt(int address, int input) {
    EEPROM.writeInt(address, input);
    EEPROM.commit();
}

float eeprom_readFloat(int address) {
    return EEPROM.readFloat(address);
}

void eeprom_writeFloat(int address, float input) {
    EEPROM.writeFloat(address, input);
    EEPROM.commit();
}