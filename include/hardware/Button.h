//
// Created by Jakub Augustýn on 14.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include <Arduino.h>

class Button {
private:
    uint8_t pin;

public:
    Button() = default;

    explicit Button(uint8_t sensorPin);

    /**
     * Reads the button state
     * @return true if the button is pressed, false otherwise
     */
    bool get() const;
};
