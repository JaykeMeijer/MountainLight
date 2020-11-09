#include "programs.h"


void Program::init() {
  // To be overriden
  name = "Default";
}

void Program::step(uint8_t r, uint8_t g, uint8_t b, int speed) {
  // To be overriden
}

void Program::step_back(uint8_t r, uint8_t g, uint8_t b, int speed) {
  // To be overriden
}

bool Program::load() {
  // To be overriden
  return true;
}

bool Program::unload() {
  // To be overriden
  return true;
}


/* Helper functions */
// void drawRainbow(uint8_t r, uint8_t g, uint8_t b, uint8_t stepSize) {
//   for (int i = 0; i < NUM_PIXELS; i++) {
//     setRow(i, makeRGBVal(r, g, b));
//     recalcRainbow(&r, &g, &b, stepSize);
//   }
// }

// void drawRainbowRev(int num_pixels, uint8_t r, uint8_t g, uint8_t b, uint8_t stepSize) {
//   for (int i = NUM_PIXELS - 1; i >= 0; i--) {
//     setRow(i, makeRGBVal(r, g, b));
//     recalcRainbowRev(&r, &g, &b, stepSize);
//   }
// }

void recalcRainbow(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t stepSize) {
  if (*r == 255 && *g == 0 && *b > 0) {
    // Phase 0
    *b = *b < stepSize ? 0 : *b - stepSize;
  } else if (*r == 255 && *g < 255 && *b == 0) {
    // Phase 1
    *g = *g + stepSize > 255 ? 255 : *g + stepSize; 
  } else if (*r > 0 && *g == 255 && *b == 0) {
    // Phase 2
    *r = *r < stepSize ? 0 : *r - stepSize;
  } else if (*r == 0 && *g == 255 && *b < 255) {
    // Phase 3
    *b = *b + stepSize > 255 ? 255 : *b + stepSize;
  } else if (*r == 0 && *g > 0 && *b == 255) {
    // Phase 4
    *g = *g < stepSize ? 0 : (*g - stepSize);
  } else {
    // Phase 6
    *r = *r + stepSize > 255 ? 255 : *r + stepSize;
  }
}


void recalcRainbowRev(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t stepSize) {
  if (*r == 255 && *g == 0 && *b < 255) {
    // Phase 0
    *b = *b + stepSize > 255 ? 255 : *b + stepSize;
  } else if (*r == 255 && *g > 0 && *b == 0) {
    // Phase 1
    *g = *g < stepSize ? 0 : (*g - stepSize);
  } else if (*r < 255 && *g == 255 && *b == 0) {
    // Phase 2
    *r = *r + stepSize > 255 ? 255 : *r + stepSize;
  } else if (*r == 0 && *g == 255 && *b > 0) {
    // Phase 3
    *b = *b < stepSize ? 0 : *b - stepSize;
  } else if (*r == 0 && *g < 255 && *b == 255) {
    // Phase 4
    *g = *g + stepSize > 255 ? 255 : *g + stepSize; 
  } else {
    // Phase 6
    *r = *r < stepSize ? 0 : *r - stepSize;
  }
}
