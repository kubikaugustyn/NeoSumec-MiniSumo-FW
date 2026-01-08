//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/TfLunaEsp32S3.h
//

#pragma once
#include <Arduino.h>
#include <TFLI2C.h> // https://github.com/budryerson/TFLuna-I2C

class Luna {
private:
    // TODO This is an awful library, we should probably just write the operations ourselves
    static TFLI2C tflI2C;

    uint8_t address;
    uint16_t threshold = 6969; // FIXME

public:
    Luna() = default;

    explicit Luna(uint8_t i2cAddress);

    /**
     * Gets the current threshold value
     * @return Current threshold value in the range from 0 cm to 1200 cm
     */
    uint16_t getThreshold() const { return threshold; }

    /**
     * Sets new threshold value
     * @param value New threshold value in the range from 0 cm to 1200 cm
     */
    void setThreshold(const uint16_t value) { threshold = value; }

    /**
     * Reads the Luna sensor value and compares it with the threshold
     * @return true if the measured value is above the threshold, false otherwise
     */
    bool get() const;

    /**
     * Reads a raw analog value from the Luna sensor
     * @return Measured distance value in the range from 0 cm to 1200 cm. Returns 0xFFFF on error.
     */
    uint16_t getRaw() const;
};


