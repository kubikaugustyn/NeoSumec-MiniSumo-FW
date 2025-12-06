//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/QRE1113.h
//

#pragma once
#include <Arduino.h>

class QRE {
private:
    uint8_t pin;
    uint16_t threshold = 3000;

public:
    QRE() = default;

    explicit QRE(uint8_t sensorPin);

    /**
     * Gets the current threshold value
     * @return Current threshold value in range from 0 (0 V) to 4096 (3.3 V)
     */
    uint16_t getThreshold() const { return threshold; }

    /**
     * Sets new threshold value
     * @param value New threshold value in range from 0 (0 V) to 4096 (3.3 V)
     */
    void setThreshold(const uint16_t value) { threshold = value; }


    /**
     * Reads the QRE sensor value and compares it with the threshold
     * @return true if the measured value is above the threshold, false otherwise
     */
    bool get() const;

    /**
     * Reads a raw analog value from the QRE sensor
     * @return Measured voltage value in range from 0 (0V) to 4096 (3.3V)
     */
    uint16_t getRaw() const;
};
