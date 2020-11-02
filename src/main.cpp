#include <Arduino.h>
#include "strands.h"
#include "api.h"
#include "state.h"

void startup() {
    Serial.begin(9600);

    for(int i = 0; i < TOTAL_PIXELS; i++) {
        //setPixelOverall(i, 127, 120, 85);
        setPixelLtR(i, 255, 255, 255);
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

    startup();
}

#define TIME 500

void prog1() {
    setAll(255, 0, 0);
    showStrips();
    delay(TIME);
    setAll(0, 255, 0);
    showStrips();
    delay(TIME);
    setAll(0, 0, 255);
    showStrips();
    delay(TIME);
    setAll(255, 255, 0);
    showStrips();
    delay(TIME);
}

void prog2() {
    setAll(255, 0, 255);
    showStrips();
    delay(50);
    setAll(0, 255, 255);
    showStrips();
    delay(50);
}

void loop() {
    switch(active_program) {
        case 1:
            prog1();
            break;
        case 2:
            prog2();
            break;
    }
    delay(100);
}