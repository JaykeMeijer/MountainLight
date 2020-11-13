#include <Arduino.h>
#include "strands.h"
#include "api.h"
#include "state.h"
#include "programs.h"

#define MIN_TIME 1000 / 30
unsigned long last_time;

void startup() {
    Serial.begin(9600);

    for(int i = 0; i < TOTAL_PIXELS; i++) {
        setPixelColorLtR(i, 255, 214, 170);
        showStrips();
        delay(10);
    }
}

void setup() {
    Serial.begin(9600);
    strands_init();

    // Don't panic, kernel
    // esp_task_wdt_init(1000, false);
    TaskHandle_t ControlTask;

    xTaskCreatePinnedToCore(
        init_api,
        "ControlTask",
        10000,
        NULL,
        0,
        &ControlTask,
        0
    );

    // Initialize program list
    loadPrograms();

    startup();

    last_time = millis();
}

int pos = 0;
int framecount = 0;

void loop() {
    // Apply color
    if (active_color_mode == 0) {
        setAllColor(active_color);
    } else {
        colors[active_color_mode - 1]->frame(color_speed);
    }

    // Apply brightness program
    if (active_effect == 0) {
        setAllBrightness(1);
    } else {
        effects[active_effect - 1]->frame(effect_speed);
    }

    showStrips();

    long sleeptime = MIN_TIME - (millis() - last_time);
    last_time = millis();
    if (sleeptime > 0) {
        delay(sleeptime);
    } else {
        late_frames++;
    }
}