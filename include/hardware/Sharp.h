//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/Sharp_GP2Y0D810Z0F.h
//

#pragma once
#include <Arduino.h>

class Sharp {
private:
    uint8_t pin;

public:
    Sharp() = default;

    explicit Sharp(uint8_t sensorPin);

    /**
     * Returns the sensor detection state
     * @return true if an object is detected, false otherwise
     */
    bool get() const;
};
