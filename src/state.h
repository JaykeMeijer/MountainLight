#include "eeprom_func.h"

#ifndef STATE_H
#define STATE_H

extern int active_program;


void load_state();
void set_state(int new_program);

#endif