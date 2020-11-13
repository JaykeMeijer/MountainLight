#include "state.h"

int active_program = 1;
int active_effect = 0;
int active_color_mode = 0;
CRGB active_color = CRGB(0, 0, 0);
float global_brightness = 1;
int effect_speed = 1;
int color_speed = 1;
int late_frames = 0;

void load_state() {
    Serial.println("Loading state");
    active_program = read_program();
    active_effect = read_effect();
    active_color_mode = read_color_mode();
    active_color = read_color();
    global_brightness = read_brightness();
    effect_speed = read_effect_speed();
    color_speed = read_color_speed();
}

int read_program() {
    return eeprom_readInt(EEPROM_PRGM);
}

int read_effect() {
    return min(eeprom_readInt(EEPROM_EFFECT), NR_EFFECTS);
}

int read_color_mode() {
    return min(eeprom_readInt(EEPROM_COLOR_MODE), NR_COLORS);
}

CRGB read_color() {
    return CRGB(
        max((uint8_t)0, min((uint8_t)255, eeprom_readByte(EEPROM_R))),
        max((uint8_t)0, min((uint8_t)255, eeprom_readByte(EEPROM_G))),
        max((uint8_t)0, min((uint8_t)255, eeprom_readByte(EEPROM_B)))
    );
}

float read_brightness() {
    return eeprom_readFloat(EEPROM_BRIGHT);
}

int read_effect_speed() {
    return max(1, eeprom_readInt(EEPROM_EFFECT_SPEED));
}

int read_color_speed() {
    return max(1, eeprom_readInt(EEPROM_COLOR_SPEED));
}

void set_program(int new_program) {
    active_program = new_program;
    eeprom_writeInt(EEPROM_PRGM, active_program);
}

void set_effect(int new_effect) {
    active_effect = min(new_effect, NR_EFFECTS);
    eeprom_writeInt(EEPROM_EFFECT, active_effect);
}

void set_color_mode(int new_color_mode) {
    active_color_mode = min(new_color_mode, NR_COLORS);
    eeprom_writeInt(EEPROM_COLOR_MODE, active_color_mode);
}

void set_color(CRGB new_color) {
    active_color = CRGB(
        max((uint8_t)0, min((uint8_t)255, new_color.r)),
        max((uint8_t)0, min((uint8_t)255, new_color.g)),
        max((uint8_t)0, min((uint8_t)255, new_color.b))
    );
    eeprom_writeByte(EEPROM_R, active_color.r);
    eeprom_writeByte(EEPROM_G, active_color.g);
    eeprom_writeByte(EEPROM_B, active_color.b);
}

void set_brightness(float new_brightness) {
    global_brightness = new_brightness;
    eeprom_writeFloat(EEPROM_BRIGHT, global_brightness);
}

void set_effect_speed(int new_effect_speed) {
    effect_speed = max(1, min(new_effect_speed, 100));
    eeprom_writeInt(EEPROM_EFFECT_SPEED, effect_speed);
}

void set_color_speed(int new_color_speed) {
    color_speed = max(1, min(new_color_speed, 100));
    eeprom_writeInt(EEPROM_COLOR_SPEED, color_speed);
}
