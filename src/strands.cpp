#include <Arduino.h>
#include "strands.h"
#include "state.h"


/* ==================== */
/* CONFIGURATION        */
/* ==================== */
CRGB s1[LEN1];
CRGB s2[LEN2];
/* ==================== */


int strands_init() {
  // Initialize FastLED lib

  FastLED.addLeds<NEOPIXEL, POR1>(s1, LEN1);
  FastLED.addLeds<NEOPIXEL, POR2>(s2, LEN2);

  // TODO create array of manually defined strands?

  setAll(0, 0, 0);
  showStrips();

  return 0;
}

/* Set an entire strand with one color */
void setAll(uint8_t r, uint8_t g, uint8_t b) {
  setStrip(s1, LEN1, r, g, b);
  setStrip(s2, LEN2, r, g, b);
}

/* Set an entire strip with one color */
void setStrip(CRGB *s, int len, uint8_t r, uint8_t g, uint8_t b) {
  r *= global_brightness;
  g *= global_brightness;
  b *= global_brightness;
  fill_solid(&(s[0]), len, CRGB(r, g, b));
}

/* Set a single pixel */
void setPixel(CRGB *s, int pixel, uint8_t r, uint8_t g, uint8_t b) {
  s[pixel].setRGB(
    r * global_brightness,
    g * global_brightness,
    b * global_brightness
  );
}

/* Set a pixel, indexed from left-to-right */
void setPixelLtR(int pixel, uint8_t r, uint8_t g, uint8_t b) {
  if (pixel < 75) {
    s1[LEN1 - 1 - pixel].setRGB(
      r * global_brightness,
      g * global_brightness,
      b * global_brightness
    );
  } else {
    s2[pixel - LEN1].setRGB(
      r * global_brightness,
      g * global_brightness,
      b * global_brightness
    );
  }
}

/* Show all strips */
void showStrips() {
  FastLED.show();
}