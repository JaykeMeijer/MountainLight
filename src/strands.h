#include <WString.h>
#include "FastLED.h"

#ifndef STRANDS_H
#define STRANDS_H

/* ==================== */
/* CONFIGURATION        */
/* ==================== */
#define TOTAL_PIXELS 120
#define STRANDS 1
#define POR1 14
#define LEN1 120
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
void setStrip(CRGB *s, uint8_t r, uint8_t g, uint8_t b);

/* Set a specific pixel on a specific strand */
void setPixel(CRGB *s, int pixel, uint8_t r, uint8_t g, uint8_t b);

/* Set a specific pixel overall */
void setPixelOverall(int pixel, uint8_t r, uint8_t g, uint8_t b);

/* Show all strips */
void showStrips();

#endif