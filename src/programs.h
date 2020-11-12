#include <WString.h>
#include "strands.h"

#ifndef PROGRAMS_H
#define PROGRAMS_H

#define NR_EFFECTS 2

class Program {
  public:
    String name;
    virtual void init();
    virtual void frame(int speed);
    virtual void frame_back(int speed);
    virtual bool load();
    virtual bool unload();
  protected:
    int current;
    int framecount;
};

extern Program **effects;

/* Effects */
class SinglePixelBackForth : public Program {
  public:
    void init();
    void frame(int speed);
    void frame_back(int speed);

  private:
    int direction;
};

class MultiPixelBackForth : public Program {
  public:
    void init();
    void frame(int speed);
    void frame_back(int speed);

  private:
    int direction;
    float gap;
};


/* Helper functions */
void drawRainbow(uint8_t r, uint8_t g, uint8_t b, uint8_t stepSize);
void drawRainbowRev(uint8_t r, uint8_t g, uint8_t b, uint8_t stepSize);
void recalcRainbow(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t stepSize);
void recalcRainbowRev(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t stepSize);

// int countProgramList();
// String loadProgramList(Program **programs, int start);

void loadPrograms();

#endif