//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/LED.h
//
#include <Arduino.h>
#include "hardware/LED.h"

LED::LED(const uint8_t ledPin) {
    pin = ledPin;
    pinMode(pin, OUTPUT);
    setOff();
}

void LED::setOn() {
    mode = ON;
    state = HIGH;
    digitalWrite(pin, HIGH);
}

void LED::setOff() {
    mode = OFF;
    state = LOW;
    digitalWrite(pin, LOW);
}

void LED::blink(const uint32_t time) {
    blink(time, time);
}

void LED::blink(const uint32_t timeOnMs, const uint32_t timeOffMs) {
    timeOn = timeOnMs;
    timeOff = timeOffMs;
    mode = BLINK;
    lastMillis = millis();
    state = HIGH;
}

void LED::update() {
    const uint32_t currentMillis = millis();

    switch (mode) {
        case OFF:
            state = LOW;
            break;
        case ON:
            state = HIGH;
            break;
        case BLINK:
            if (state == HIGH && currentMillis - lastMillis >= timeOn) {
                state = LOW;
                lastMillis = currentMillis;
            } else if (state == LOW && currentMillis - lastMillis >= timeOff) {
                state = HIGH;
                lastMillis = currentMillis;
            }
            break;
    }

    digitalWrite(pin, state);
}
