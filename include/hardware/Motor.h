//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/Motor.h
//

#ifndef NEOSUMEC_SW_MOTOR_H
#define NEOSUMEC_SW_MOTOR_H
/*
* Truthtable
* ╔═════════╤═══════╤═══════╦═══════════╗
* ║nSleep	│EN		│PH		║Status		║
* ╠═════════╪═══════╪═══════╬═══════════╣
* ║0		│any	│any	║Sleep		║
* ╟─────────┼───────┼───────╫───────────╢
* ║1		│0		│any	║Brake		║
* ╟─────────┼───────┼───────╫───────────╢
* ║1		│1		│0		║Backward	║
* ╟─────────┼───────┼───────╫───────────╢
* ║1		│1		│1		║Forward	║
* ╚═════════╧═══════╧═══════╩═══════════╝
* this means that if pwm is OFF, robot BRAKES
* if PH is 0 robot goes BACKWARD, 1 robot goes FORWARD
*/

#include <Arduino.h>
#define PWM_RESOLUTION	8
#define PWM_MAX_VALUE	((1 << (PWM_RESOLUTION)) - 1)
#define PWM_FREQUENCY	5000

class Motor {
private:
    uint8_t sleepPin; // nSLEEP pin
    uint8_t enablePin; // EN/IN1 pin
    uint8_t phasePin; // PH/IN2 pin
    uint8_t channel;
    uint8_t resolution;
    uint32_t frequency;

public:
    Motor() = default;

    Motor(uint8_t sleepPin, uint8_t enablePin, uint8_t phasePin, uint8_t channel);

    void goForward() const;

    void goBackward() const;

    void stop() const;

    void drive(float speed) const;
};
#endif //NEOSUMEC_SW_MOTOR_H
