#include <Arduino.h>
#include "strands.h"



/* ==================== */
/* CONFIGURATION        */
/* ==================== */
CRGB s1[LEN1];
/* ==================== */


int strands_init() {
  // Initialize FastLED lib

  FastLED.addLeds<NEOPIXEL, POR1>(s1, LEN1);

  // TODO create array of manually defined strands?

  setStrip(s1, 0, 0, 0);
  showStrips();

  return 0;
}

/* Set an entire strand with one color */
void setAll(uint8_t r, uint8_t g, uint8_t b) {
  setStrip(s1, r, g, b);
}

/* Set an entire strip with one color */
void setStrip(CRGB *s, uint8_t r, uint8_t g, uint8_t b) {
  // TODO check out fill_solid from fastled
  // for (int i = 0; i < 120; i++) {
  //   strands[strand].pixels[i].setRGB(r, g, b);
  // }
  fill_solid(&(s[0]), LEN1, CRGB(r, g, b));
}

/* Set a single pixel */
void setPixel(CRGB *s, int pixel, uint8_t r, uint8_t g, uint8_t b) {
  s[pixel].setRGB(r, g, b);
}

void setPixelOverall(int pixel, uint8_t r, uint8_t g, uint8_t b) {
  // TODO implement logic over strands
  s1[pixel].setRGB(r, g, b);
}

/* Show all strips */
void showStrips() {
  FastLED.show();
}