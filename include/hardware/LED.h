//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/LED.h
//

#pragma once
#include <Arduino.h>

class LED {
private:
    enum Mode : uint8_t { OFF = 0, ON, BLINK };

    uint8_t pin;
    uint32_t lastMillis = 0;
    Mode mode = OFF;
    uint8_t state = LOW;
    uint32_t timeOn, timeOff;

public:
    LED() = default;

    explicit LED(uint8_t ledPin);

    void setOn();

    void setOff();

    void blink(uint32_t time);

    void blink(uint32_t timeOnMs, uint32_t timeOffMs);

    void update();
};
