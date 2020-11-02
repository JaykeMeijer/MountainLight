#include "eeprom_func.h"

#ifndef STATE_H
#define STATE_H

extern int active_program;
extern float global_brightness;


void load_state();
int read_program();
float read_brightness();
void set_program(int new_program);
void set_brightness(float new_brightness);

#endif