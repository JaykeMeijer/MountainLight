#include "eeprom_func.h"

#ifndef STATE_H
#define STATE_H

extern int active_program;
extern int active_effect;
extern float global_brightness;

extern int late_frames;


void load_state();
int read_program();
int read_effect();
float read_brightness();
void set_program(int new_program);
void set_effect(int new_effect);
void set_brightness(float new_brightness);

#endif