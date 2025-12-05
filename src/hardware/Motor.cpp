//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/Motor.h
//

#include "hardware/Motor.h"

Motor::Motor(const uint8_t sleepPin, const uint8_t enablePin, const uint8_t phasePin, const uint8_t channel) {
    this->sleepPin = sleepPin;
    this->enablePin = enablePin;
    this->phasePin = phasePin;
    this->channel = channel;

    // set nSLEEP pin
    pinMode(sleepPin, OUTPUT);
    digitalWrite(sleepPin, 1);

    // set PH pin
    pinMode(phasePin, OUTPUT);
    goForward();

    // set EN pin
    ledcAttachPin(enablePin, channel);
    ledcSetup(channel, PWM_FREQUENCY, PWM_RESOLUTION);

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

/*void Motor::setSpeed(float speed) const {
    // TO DO: limit setpoint to 0..1

    // ledcWrite(mChannel, speed*(float)PWM_MAX_VALUE);

    ledcWrite(channel, speed * 255);
}*/

void Motor::drive(float speed) const {
    // Clamp speed to -1..1
    if (speed > 1.0f) speed = 1.0f;
    if (speed < -1.0f) speed = -1.0f;

    // Motor awake
    digitalWrite(sleepPin, HIGH);

    // Stop / brake
    if (fabs(speed) < 1e-6) {
        ledcWrite(channel, 0); // EN = 0 → Brake
        return;
    }

    // Direction: PH = 1 forward, PH = 0 backward
    digitalWrite(phasePin, speed > 0);

    // PWM magnitude
    const uint32_t duty = static_cast<uint32_t>(fabs(speed) * PWM_MAX_VALUE);
    ledcWrite(channel, duty);
}
