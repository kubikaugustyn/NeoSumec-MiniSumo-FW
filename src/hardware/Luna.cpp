//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/TfLunaEsp32S3.h
//

#include "hardware/Luna.h"

TFLI2C Luna::tflI2C{}; // Construct the object

Luna::Luna(const uint8_t i2cAddress) {
    address = i2cAddress;
}

bool Luna::get() const {
    return getRaw() < threshold;
}

uint16_t Luna::getRaw() const {
    int16_t dist, flux, temp;
    const bool success = tflI2C.getData(dist, flux, temp, address);
    if (!success || dist < 0) return 0xFFFF;
    return static_cast<uint16_t>(dist);
}
