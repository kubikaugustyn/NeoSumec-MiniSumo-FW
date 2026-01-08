//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "MainConfig.h" // Required to "load" the current pinout

// ===== MK5 pins =====
#ifdef PINOUT_NEOSUMEC_PINS_MK5
// H-bridge pins - left motor
#define PIN_MOTOR_LEFT_NSLEEP   11
#define PIN_MOTOR_LEFT_ENABLE   14
#define PIN_MOTOR_LEFT_PHASE    12
#define MOTOR_LEFT_CHANNEL      0
// H-bridge pins - right motor
#define PIN_MOTOR_RIGHT_NSLEEP  11
#define PIN_MOTOR_RIGHT_ENABLE  21
#define PIN_MOTOR_RIGHT_PHASE   13
#define MOTOR_RIGHT_CHANNEL     1
// QRE sensor pins
#define PIN_QRE_LEFT            10
#define PIN_QRE_RIGHT           9
#define PIN_QRE_REAR            8
// Side-facing Sharp sensor pins
#define PIN_SHARP_LEFT          35
#define PIN_SHARP_RIGHT         16
// I2C bus for Luna sensors
#define PIN_I2C_SDA             18
#define PIN_I2C_SCL             17
#define I2C_FREQUENCY           400000
// Front-facing Luna sensor I2C addresses
#define I2C_ADDRESS_LUNA_LEFT   0x11
#define I2C_ADDRESS_LUNA_MIDDLE 0x10
#define I2C_ADDRESS_LUNA_RIGHT  0x13
// LED pins
#define PIN_LED_RED             47
#define PIN_LED_ORANGE          48
// IR sensor pin
#define PIN_IR                  38
// Button
#define PIN_BUTTON              2
#endif // PINOUT_NEOSUMEC_PINS_MK5
// ===== MK5 pins end =====
