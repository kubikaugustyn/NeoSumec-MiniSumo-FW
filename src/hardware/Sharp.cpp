//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/Sharp_GP2Y0D810Z0F.h
//

#include "hardware/Sharp.h"

Sharp::Sharp(const uint8_t sensorPin) {
    pin = sensorPin;
    pinMode(pin, INPUT);
}

bool Sharp::get() const {
    return !digitalRead(pin);
}
