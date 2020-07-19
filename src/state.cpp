#include "state.h"

int active_program = 1;

void load_state() {
    Serial.println("Loading state");
    active_program = eeprom_readInt(EEPROM_PRGM);
    Serial.println(active_program);
}

int read_program() {
    return eeprom_readInt(EEPROM_PRGM);
}

void set_program(int new_program) {
    active_program = new_program;
    eeprom_writeInt(EEPROM_PRGM, active_program);
    Serial.println("Written to EEPROM");
    Serial.println(active_program);
}
