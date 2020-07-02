#include <WString.h>
#include "strands.h"

#ifndef PROGRAMS_H
#define PROGRAMS_H

#define MAX_SPEED 10

class Program {
  public:
    String name;
    virtual void init();
    virtual void step(uint8_t r, uint8_t g, uint8_t b, int speed);
    virtual void step_back(uint8_t r, uint8_t g, uint8_t b, int speed);
    virtual bool load();
    virtual bool unload();
  protected:
    int current;
};


/* Helper functions */
void drawRainbow(uint8_t r, uint8_t g, uint8_t b, uint8_t stepSize);
void drawRainbowRev(uint8_t r, uint8_t g, uint8_t b, uint8_t stepSize);
void recalcRainbow(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t stepSize);
void recalcRainbowRev(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t stepSize);

int countProgramList();
String loadProgramList(Program **programs, int start);

void setBlackout();

#endif