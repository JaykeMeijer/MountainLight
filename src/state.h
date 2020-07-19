#include "eeprom_func.h"

#ifndef STATE_H
#define STATE_H

extern int active_program;


void load_state();
int read_program();
void set_program(int new_program);

#endif