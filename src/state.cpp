#include "state.h"

int active_program = 1;
int active_effect = 0;
float global_brightness = 1;
int effect_speed = 1;
int late_frames = 0;

void load_state() {
    Serial.println("Loading state");
    active_program = read_program();
    active_effect = read_effect();
    global_brightness = read_brightness();
    effect_speed = read_effect_speed();
}

int read_program() {
    return eeprom_readInt(EEPROM_PRGM);
}

int read_effect() {
    return min(eeprom_readInt(EEPROM_EFFECT), NR_EFFECTS);
}

float read_brightness() {
    return eeprom_readFloat(EEPROM_BRIGHT);
}

int read_effect_speed() {
    return max(1, eeprom_readInt(EEPROM_EFFECT_SPEED));
}

void set_program(int new_program) {
    active_program = new_program;
    eeprom_writeInt(EEPROM_PRGM, active_program);
}

void set_effect(int new_effect) {
    active_effect = min(new_effect, NR_EFFECTS);
    eeprom_writeInt(EEPROM_EFFECT, active_effect);
}

void set_brightness(float new_brightness) {
    global_brightness = new_brightness;
    eeprom_writeFloat(EEPROM_BRIGHT, global_brightness);
}

void set_effect_speed(int new_effect_speed) {
    effect_speed = max(1, min(new_effect_speed, 100));
    eeprom_writeInt(EEPROM_EFFECT_SPEED, effect_speed);
}
