#include "eeprom_func.h"
#include "programs.h"

#ifndef STATE_H
#define STATE_H

extern int active_program;
extern int active_effect;
extern int effect_speed;
extern float global_brightness;

extern int late_frames;


void load_state();
int read_program();
int read_effect();
float read_brightness();
int read_effect_speed();
void set_program(int new_program);
void set_effect(int new_effect);
void set_brightness(float new_brightness);
void set_effect_speed(int new_speed);

#endif