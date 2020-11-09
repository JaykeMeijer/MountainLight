#include <Arduino.h>
#include "strands.h"
#include "api.h"
#include "state.h"

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

    startup();

    last_time = millis();
}

int pos = 0;
int framecount = 0;

void loop() {
    // Apply color
    setAllColor(255, 214, 170);

    // Apply brightness program
    if (active_effect == 1) {
        if (framecount == 30) {
            setAllBrightness(0.3);
            setPixelBrightnessLtR(pos, 1);
            framecount = 0;
            pos++;
            pos = pos % 120;
        } else {
            framecount++;
        }
    } else {
        setAllBrightness(1);
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