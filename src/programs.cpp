#include "programs.h"

Program **effects;

void loadPrograms() {
  effects = (Program**)malloc(sizeof(Program*) * NR_EFFECTS);
  effects[0] = new SinglePixelBackForth();
  effects[1] = new MultiPixelBackForth();

  /* Init effects */
  for (int i = 0; i < NR_EFFECTS; i++) {
    effects[i]->init();
  }
}


void Program::init() {
  // To be overriden
  name = "Default";
}

void Program::frame(int speed) {
  // To be overriden
}

void Program::frame_back(int speed) {
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

void SinglePixelBackForth::init() {
  name = "Single Pixel Echo";
  current = 0;
  framecount = 0;
  direction = 1;
}

void SinglePixelBackForth::frame(int speed) {
  if (framecount > (200 / speed)) {
    if (current == 119) {
      direction = -1;
    } else if (current == 0) {
      direction = 1;
    }
    current += direction;
    setAllBrightness(0.3);
    setPixelBrightnessLtR(current, 1);
    framecount = 0;
  } else {
    framecount++;
  }
}

void SinglePixelBackForth::frame_back(int speed) {
  frame(speed);
}


void MultiPixelBackForth::init() {
  name = "Multi Pixel Echo";
  current = 0;
  framecount = 0;
  direction = 1;
  gap = 0.7 / 15;
}

void MultiPixelBackForth::frame(int speed) {
  if (framecount > (200 / speed)) {
    if (current == TOTAL_PIXELS_MIN_1) {
      direction = -1;
    } else if (current == 0) {
      direction = 1;
    }
    current += direction;
    setAllBrightness(0.3);
    int rangelim = max(0, current - 15);
    for (int i = rangelim; i < current; i++) {
      setPixelBrightnessLtR(i, 0.3 + (15 - (current - i)) * gap);
    }
    setPixelBrightnessLtR(current, 1);
    rangelim = min(TOTAL_PIXELS, current + 15);
    for (int i = current + 1; i < rangelim; i++) {
      setPixelBrightnessLtR(i, 0.3 + (15 - (i - current)) * gap);
    }
    framecount = 0;
  } else {
    framecount++;
  }
}

void MultiPixelBackForth::frame_back(int speed) {
  frame(speed);
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
