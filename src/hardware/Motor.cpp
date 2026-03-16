//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/Motor.h
//

#include "hardware/Motor.h"

void Motor::begin(const uint8_t sleepPin_, const uint8_t enablePin_, const uint8_t phasePin_, const uint8_t channel_,
             const float speedMultiplier_) {
    sleepPin = sleepPin_;
    enablePin = enablePin_;
    phasePin = phasePin_;
    channel = channel_;
    speedMultiplier = speedMultiplier_;

    // set nSLEEP pin
    pinMode(sleepPin_, OUTPUT);
    digitalWrite(sleepPin_, HIGH);

    // set PH pin
    pinMode(phasePin_, OUTPUT);
    goForward();

    // set EN pin
    // LEDC setup order is important!
    ledcSetup(channel_, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(enablePin_, channel_);

    stop();
}

void Motor::goForward() const {
    drive(1.0f);
}

void Motor::goBackward() const {
    drive(-1.0f);
}

void Motor::stop() const {
    drive(0.0f);
}

void Motor::drive(float speed) const {
    // Clamp speed to -1..1
    if (speed > 1.0f) speed = 1.0f;
    if (speed < -1.0f) speed = -1.0f;

    speed *= speedMultiplier;

    // Ensure the motor is awake
    digitalWrite(sleepPin, HIGH);

    // Stop / brake
    if (fabs(speed) < 1e-6) {
        ledcWrite(channel, 0); // EN = 0 → Brake
        return;
    }

    // Direction: PH = 1 forward, PH = 0 backward
    digitalWrite(phasePin, speed > 0 ? HIGH : LOW);

    // PWM magnitude
    const uint32_t duty = static_cast<uint32_t>(fabs(speed) * PWM_MAX_VALUE);
    ledcWrite(channel, duty);
}
