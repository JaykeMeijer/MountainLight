#include <WString.h>
#define FASTLED_ESP32_I2S true
#include "FastLED.h"

#ifndef STRANDS_H
#define STRANDS_H

/* ==================== */
/* CONFIGURATION        */
/* ==================== */
#define TOTAL_PIXELS 120
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
void setAll(uint8_t r, uint8_t g, uint8_t b);

/* Set an entire strip with one color */
void setStrip(CRGB *s, int len, uint8_t r, uint8_t g, uint8_t b);

/* Set a specific pixel on a specific strand */
void setPixel(CRGB *s, int pixel, uint8_t r, uint8_t g, uint8_t b);

/* Set a specific pixel overall */
void setPixelLtR(int pixel, uint8_t r, uint8_t g, uint8_t b);

/* Show all strips */
void showStrips();

#endif