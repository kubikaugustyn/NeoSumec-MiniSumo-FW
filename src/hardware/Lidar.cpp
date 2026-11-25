//
// Created by Jakub Augustýn on 25.11.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "hardware/Lidar.h"

void Lidar::begin(const uint8_t sensorPin) {
    pin = sensorPin;
    pinMode(pin, INPUT);
}

uint16_t Lidar::getRaw() const {
    const unsigned long time = pulseIn(pin, HIGH, 30000);
    if (time == 0 || time > 1850) return 0xFFFF; // Timeout or no detection

    uint16_t distance = (time - 1000) / 5; // * 2 (mm) / 10 (--> cm)
    if (distance < 0) distance = 0;
    return distance;
}
