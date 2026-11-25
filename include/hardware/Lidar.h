//
// Created by Jakub Augustýn on 25.11.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// Pololu Lidar Distance sensor
// https://www.pololu.com/product/4071
//

#pragma once
#include <Arduino.h>

// TODO Add a threshold system just like the one in the Luna
// TODO Allow reading sub-millimeter values instead of centimeters
class Lidar {
private:
    uint8_t pin{};

public:
    Lidar() = default;

    void begin(uint8_t sensorPin);

    /**
     * Reads a raw distance value from the Lidar sensor
     * @return Measured distance value in the range from 0 cm to 130 cm. Returns 0xFFFF on error.
     */
    uint16_t getRaw() const;
};
