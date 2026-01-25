//
// Created by Jakub Augustýn on 14.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "hardware/Button.h"

Button::Button(const uint8_t sensorPin) {
    pin = sensorPin;
    pinMode(pin, INPUT_PULLDOWN);
}

bool Button::get() const {
    return digitalRead(pin);
}
