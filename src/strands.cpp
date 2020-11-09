#include <Arduino.h>
#include "strands.h"
#include "state.h"


/* ==================== */
/* CONFIGURATION        */
/* ==================== */
CRGB c1[LEN1];
CRGB c2[LEN2];
float b1[LEN1];
float b2[LEN2];
CRGB s1[LEN1];
CRGB s2[LEN2];
/* ==================== */


int strands_init() {
  // Initialize FastLED lib

  FastLED.addLeds<NEOPIXEL, POR1>(s1, LEN1);
  FastLED.addLeds<NEOPIXEL, POR2>(s2, LEN2);

  // TODO create array of manually defined strands?

  setAllColor(0, 0, 0);
  setAllBrightness(1);
  showStrips();

  return 0;
}

/* Set an entire strand with one color */
void setAllColor(uint8_t r, uint8_t g, uint8_t b) {
  setStripColor(c1, LEN1, r, g, b);
  setStripColor(c2, LEN2, r, g, b);
}

void setAllBrightness(float brightness) {
  setStripBrightness(b1, LEN1, brightness);
  setStripBrightness(b2, LEN2, brightness);
}

/* Set an entire strip with one color */
void setStripColor(CRGB *c, int len, uint8_t r, uint8_t g, uint8_t b) {
  fill_solid(&(c[0]), len, CRGB(r, g, b));
}

void setStripBrightness(float *b, int len, float brightness) {
  for (int i = 0; i < len; i++) {
    b[i] = brightness;
  }
}

/* Set a single pixel */
void setPixelColor(CRGB *c, int pixel, uint8_t r, uint8_t g, uint8_t b) {
  c[pixel].setRGB(r, g, b);
}

/* Set a pixel, indexed from left-to-right */
void setPixelColorLtR(int pixel, uint8_t r, uint8_t g, uint8_t b) {
  if (pixel < 75) {
    c1[LEN1 - 1 - pixel].setRGB(r, g, b);
  } else {
    c2[pixel - LEN1].setRGB(r, g, b);
  }
}

/* Apply a brightness effect over a pixel. */
void setPixelBrightnessLtR(int pixel, float brightness) {
  if (pixel < 75) {
    b1[LEN1 - 1 - pixel] = brightness;
  } else {
    b2[pixel - LEN1] = brightness;
  }
}

/* Show all strips */
void showStrips() {
  for (int i = 0; i < LEN1; i++) {
    s1[i].r = uint8_t(c1[i].r * b1[i] * global_brightness);
    s1[i].g = uint8_t(c1[i].g * b1[i] * global_brightness);
    s1[i].b = uint8_t(c1[i].b * b1[i] * global_brightness);
  }
  for (int i = 0; i < LEN2; i++) {
    s2[i].r = uint8_t(c2[i].r * b2[i] * global_brightness);
    s2[i].b = uint8_t(c2[i].b * b2[i] * global_brightness);
    s2[i].g = uint8_t(c2[i].g * b2[i] * global_brightness);
  }
  FastLED.show();
}