//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/QRE1113.h
//

#include "hardware/QRE.h"

QRE::QRE(const uint8_t sensorPin) {
    pin = sensorPin;
    pinMode(pin, INPUT);
}

bool QRE::get() const {
    return getRaw() < threshold;
}

uint16_t QRE::getRaw() const {
    return analogRead(pin);
}
