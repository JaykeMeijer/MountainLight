#include "eeprom_func.h"
#include "programs.h"
#include "strands.h"

#ifndef STATE_H
#define STATE_H

extern int active_program;
extern int active_effect;
extern int active_color_mode;
extern CRGB active_color;
extern int effect_speed;
extern int color_speed;
extern float global_brightness;

extern int late_frames;


void load_state();
int read_program();
int read_effect();
int read_color_mode();
CRGB read_color();
float read_brightness();
int read_effect_speed();
int read_color_speed();
void set_program(int new_program);
void set_effect(int new_effect);
void set_color_mode(int new_color_mode);
void set_color(CRGB new_color);
void set_brightness(float new_brightness);
void set_effect_speed(int new_speed);
void set_color_speed(int new_speed);

#endif