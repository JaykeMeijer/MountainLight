#include <WString.h>
#define FASTLED_ESP32_I2S true
#include "FastLED.h"

#ifndef STRANDS_H
#define STRANDS_H

/* ==================== */
/* CONFIGURATION        */
/* ==================== */
#define TOTAL_PIXELS 120
#define TOTAL_PIXELS_MIN_1 119
#define STRANDS 2
#define POR1 27
#define POR2 26
#define LEN1 75
#define LEN2 45
/* ==================== */

typedef struct {
  int gpioNum;
  int numPixels;
  CRGB * pixels;
} strand_t;

int strands_init();

/* Set an entire strand with one color */
void setAllColor(uint8_t r, uint8_t g, uint8_t b);
void setAllColor(CRGB color);
void setAllBrightness(float brightness);

/* Set an entire strip with one color */
void setStripColor(CRGB *s, int len, uint8_t r, uint8_t g, uint8_t b);
void setStripColor(CRGB *s, int len, CRGB color);
void setStripBrightness(float *b, int len, float brightness);

/* Set a specific pixel on a specific strand */
void setPixelColor(CRGB *s, int pixel, uint8_t r, uint8_t g, uint8_t b);
void setPixelColor(CRGB *s, int pixel, CRGB color);

/* Set a specific pixel overall */
void setPixelColorLtR(int pixel, uint8_t r, uint8_t g, uint8_t b);
void setPixelColorLtR(int pixel, CRGB color);
void setPixelBrightnessLtR(int pixel, float brightness);

/* Show all strips */
void showStrips();

#endif