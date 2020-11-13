#include "programs.h"

Program **colors;
Program **effects;

void loadPrograms() {
  colors = (Program**)malloc(sizeof(Program*) * NR_COLORS);
  colors[0] = new StaticRainbow();
  colors[1] = new MovingRainbow();
  colors[2] = new Mountain();

  effects = (Program**)malloc(sizeof(Program*) * NR_EFFECTS);
  effects[0] = new SinglePixelBackForth();
  effects[1] = new MultiPixelBackForth();
  effects[2] = new Pulse();
  effects[3] = new Heartbeat();

  /* Init colors */
  for (int i = 0; i < NR_COLORS; i++) {
    colors[i]->init();
  }

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

bool Program::load() {
  // To be overriden
  return true;
}

bool Program::unload() {
  // To be overriden
  return true;
}

void StaticRainbow::init() {
  name = "Static Rainbow";
  framecount = 1000;
  r = 255;
  g = 0;
  b = 0;
}

void StaticRainbow::frame(int speed) {
  if (framecount > (100 / speed)) {
    recalcRainbow(&r, &g, &b, 2);
    setAllColor(r, g, b);
    framecount = 0;
  } else {
    framecount++;
  }
}

void MovingRainbow::init() {
  name = "Moving Rainbow";
  framecount = 1000;
  r = 255;
  g = 0;
  b = 0;
}

void MovingRainbow::frame(int speed) {
  if (framecount > (100 / speed)) {
    uint8_t l_r = r;
    uint8_t l_g = g;
    uint8_t l_b = b;
    for (int i = TOTAL_PIXELS - 1; i >= 0; i--) {
      setPixelColorLtR(i, l_r, l_g, l_b);
      recalcRainbow(&l_r, &l_g, &l_b, 5);
    }
    recalcRainbow(&r, &g, &b, 5);
    framecount = 0;
  } else {
    framecount++;
  }
}

void Mountain::init() {
  name = "Mountain";
  g = CRGB(0, 64, 0);
  w = CRGB(255, 255, 255);
}

void Mountain::frame(int speed) {
  for (int i = 0; i < 20; i++) {
    setPixelColorLtR(i, g);
  }
  for (int i = 20; i < 32; i++) {
    setPixelColorLtR(i, w);
  }
  for (int i = 32; i < 45; i++) {
    setPixelColorLtR(i, g);
  }
  for (int i = 45; i < 48; i++) {
    setPixelColorLtR(i, w);
  }
  for (int i = 49; i < 60; i++) {
    setPixelColorLtR(i, g);
  }
  for (int i = 60; i < 87; i++) {
    setPixelColorLtR(i, w);
  }
  for (int i = 87; i < 120; i++) {
    setPixelColorLtR(i, g);
  }
}

void SinglePixelBackForth::init() {
  name = "Single Pixel Echo";
  current = 0;
  framecount = 1000;
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

void MultiPixelBackForth::init() {
  name = "Multi Pixel Echo";
  current = 0;
  framecount = 1000;
  direction = 1;
  gap = 0.8 / 15;
}

void MultiPixelBackForth::frame(int speed) {
  if (framecount > (200 / speed)) {
    if (current == TOTAL_PIXELS_MIN_1) {
      direction = -1;
    } else if (current == 0) {
      direction = 1;
    }
    current += direction;
    setAllBrightness(0.2);
    int rangelim = max(0, current - 15);
    for (int i = rangelim; i < current; i++) {
      setPixelBrightnessLtR(i, 0.2 + (15 - (current - i)) * gap);
    }
    setPixelBrightnessLtR(current, 1);
    rangelim = min(TOTAL_PIXELS, current + 15);
    for (int i = current + 1; i < rangelim; i++) {
      setPixelBrightnessLtR(i, 0.2 + (15 - (i - current)) * gap);
    }
    framecount = 0;
  } else {
    framecount++;
  }
}

void Pulse::init() {
  name = "Pulse";
  current = 0;
  framecount = 1000;
  direction = 1;
}

void Pulse::frame(int speed) {
  if (framecount > (100 / speed)) {
    if (current >= 255) {
      direction = -1;
      current = 255;
    } else if (current <= 0) {
      direction = 1;
      current = 0;
    }
    setAllBrightness(current / 255.0);
    current += direction;
    framecount = 0;
  } else {
    framecount++;
  }
}

void Heartbeat::init() {
  name = "Heartbeat";
  current = 120;
  framecount = 1000;
  direction = 8;
  gap = false;
  wave = 0;
}

void Heartbeat::frame(int speed) {
  if ((!gap && framecount) || framecount > (4000 / speed)) {
    gap = false;
    if (current >= 255) {
      direction = -10;
      current = 255;
    } else if (current <= 80 ) {
      direction = 10;
      current = 80;
      wave++;
      if (wave == 2) {
        gap = true;
        wave = 0;
      }
    }
    setAllBrightness(current / 255.0);
    current += direction;
    framecount = 0;
  } else {
    framecount++;
  }
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
