//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "MainConfig.h" // Required to "load" the current pinout

// ===== MK3 pins =====
#ifdef PINOUT_SUMEC_PINS_MK3
// H-bridge pins - left motor
#define PIN_MOTOR_LEFT_NSLEEP   11
#define PIN_MOTOR_LEFT_ENABLE   14
#define PIN_MOTOR_LEFT_PHASE    12
#define MOTOR_LEFT_CHANNEL      0
#define MOTOR_LEFT_SCALE        1.0f
// H-bridge pins - right motor
#define PIN_MOTOR_RIGHT_NSLEEP  11
#define PIN_MOTOR_RIGHT_ENABLE  21
#define PIN_MOTOR_RIGHT_PHASE   13
#define MOTOR_RIGHT_CHANNEL     1
#define MOTOR_RIGHT_SCALE       1.0f
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
#endif // PINOUT_SUMEC_PINS_MK3
// ===== MK3 pins end =====

// ===== MK5 pins =====
#ifdef PINOUT_SUMEC_PINS_MK5
//================================
// I2C Addresses
// EEPROM ->            0x50
// BNO055 (IMU) ->      0x28/0x29
// INA226 (VolAlert)->  0x40
//================================
// H-bridge pins - left motor
#define PIN_MOTOR_LEFT_NSLEEP   9
#define PIN_MOTOR_LEFT_ENABLE   17
#define PIN_MOTOR_LEFT_PHASE    18
#define MOTOR_LEFT_CHANNEL      0
#define MOTOR_LEFT_SCALE        1.0f
// Encoder outputs - left motor
#define PIN_LEFT_ENCODER_OUT_A  42
#define PIN_LEFT_ENCODER_OUT_B  41
// H-bridge pins - right motor
#define PIN_MOTOR_RIGHT_NSLEEP  9
#define PIN_MOTOR_RIGHT_ENABLE  15
#define PIN_MOTOR_RIGHT_PHASE   16
#define MOTOR_RIGHT_CHANNEL     1
#define MOTOR_RIGHT_SCALE       1.0f
// Encoder outputs - right motor
#define PIN_RIGHT_ENCODER_OUT_A 4
#define PIN_RIGHT_ENCODER_OUT_B 5
// QRE sensor pins
#define PIN_QRE_LEFT            13
#define PIN_QRE_RIGHT           48
#define PIN_QRE_REAR            1
// Side-facing Sharp sensor pins
#define PIN_SHARP_LEFT          10
#define PIN_SHARP_RIGHT         40
// I2C bus for Luna sensors
#define PIN_I2C_SDA             36
#define PIN_I2C_SCL             35
#define I2C_FREQUENCY           400000
// Front-facing Luna sensor I2C addresses
#define I2C_ADDRESS_LUNA_MIDDLE 0x10
// No left and right Luna sensors, instead has Lidar sensors
#define PIN_LIDAR_LEFT          37
#define PIN_LIDAR_RIGHT         11
// LED pins
#define PIN_LED_RED             47 // PCB: LED_IO47
#define PIN_LED_ORANGE          14 // PCB: LED_IO14
#define PIN_LED_IO21            47 // PCB: LED_IO21
// IR sensor pin
#define PIN_IR                  38
// Button
#define PIN_BUTTON              6 // PCB: SW1
#define PIN_BUTTON_OI7          7 // PCB: SW2
// Voltage alert
#define PIN_VOLTAGE_ALERT       8 // TODO Figure out how that works
// 9-axis IMU
#define PIN_IMU                 39
#endif // PINOUT_SUMEC_PINS_MK5
// ===== MK5 pins end =====
