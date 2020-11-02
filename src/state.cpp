#include "state.h"

int active_program = 1;
float global_brightness = 1;

void load_state() {
    Serial.println("Loading state");
    active_program = eeprom_readInt(EEPROM_PRGM);
    global_brightness = eeprom_readFloat(EEPROM_BRIGHT);
    Serial.println(active_program);
}

int read_program() {
    return eeprom_readInt(EEPROM_PRGM);
}

float read_brightness() {
    return eeprom_readFloat(EEPROM_BRIGHT);
}

void set_program(int new_program) {
    active_program = new_program;
    eeprom_writeInt(EEPROM_PRGM, active_program);
    Serial.println("Written to EEPROM");
    Serial.println(active_program);
}

void set_brightness(float new_brightness) {
    global_brightness = new_brightness;
    eeprom_writeFloat(EEPROM_BRIGHT, global_brightness);
    Serial.println("Written to EEPROM");
    Serial.println(global_brightness);
}
