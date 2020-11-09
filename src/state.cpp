#include "state.h"

int active_program = 1;
int active_effect = 0;
float global_brightness = 1;
int late_frames = 0;

void load_state() {
    Serial.println("Loading state");
    active_program = eeprom_readInt(EEPROM_PRGM);
    active_effect = eeprom_readInt(EEPROM_EFFECT);
    global_brightness = eeprom_readFloat(EEPROM_BRIGHT);
    Serial.println(active_program);
}

int read_program() {
    return eeprom_readInt(EEPROM_PRGM);
}

int read_effect() {
    return eeprom_readInt(EEPROM_EFFECT);
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

void set_effect(int new_effect) {
    active_effect = new_effect;
    eeprom_writeInt(EEPROM_EFFECT, active_effect);
    Serial.println("Written to EEPROM");
    Serial.println(active_effect);
}

void set_brightness(float new_brightness) {
    global_brightness = new_brightness;
    eeprom_writeFloat(EEPROM_BRIGHT, global_brightness);
    Serial.println("Written to EEPROM");
    Serial.println(global_brightness);
}
