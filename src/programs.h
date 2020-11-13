#include <WString.h>
#include "strands.h"

#ifndef PROGRAMS_H
#define PROGRAMS_H

#define NR_EFFECTS 4
#define NR_COLORS 3

class Program {
  public:
    String name;
    virtual void init();
    virtual void frame(int speed);
    virtual bool load();
    virtual bool unload();
  protected:
    int current;
    int framecount;
};

extern Program **colors;
extern Program **effects;

/* Colors */
class StaticRainbow : public Program {
  public:
    void init();
    void frame(int speed);

  private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class MovingRainbow : public Program {
  public:
    void init();
    void frame(int speed);

  private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Mountain : public Program {
  public:
    void init();
    void frame(int speed);

  private:
    CRGB g;
    CRGB w;
};

/* Effects */
class SinglePixelBackForth : public Program {
  public:
    void init();
    void frame(int speed);

  private:
    int direction;
};

class MultiPixelBackForth : public Program {
  public:
    void init();
    void frame(int speed);

  private:
    int direction;
    float gap;
};

class Pulse : public Program {
  public:
    void init();
    void frame(int speed);

  private:
    int direction;
};


class Heartbeat : public Program {
  public:
    void init();
    void frame(int speed);

  private:
    int direction;
    bool gap;
    int wave;
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