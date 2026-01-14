//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "hardware/Robot.h"

#include <Wire.h>

#include "hardware/Pins.h"

void Robot::begin() {
    leftMotor = Motor(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL);
    rightMotor = Motor(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL);
    drive = DriveBase(leftMotor, rightMotor);

    ledRed = LED(PIN_LED_RED);
    ledOrange = LED(PIN_LED_ORANGE);

    startButton = Button(PIN_BUTTON);

    lineSensorLeft = QRE(PIN_QRE_LEFT);
    lineSensorRight = QRE(PIN_QRE_RIGHT);
    lineSensorRear = QRE(PIN_QRE_REAR);
    // FIXME Do we want this?
    // https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/37f0c36fc5ec6d57ca9154137380c8463f6ad914/main_sw/MAIN_CODE/src/main.cpp#L60-L61
    // lineSensorLeft.setThreshold(1800);
    // lineSensorRight.setThreshold(1800);

    leftProximity = Sharp(PIN_SHARP_LEFT);
    rightProximity = Sharp(PIN_SHARP_RIGHT);

    Wire.begin(PIN_I2C_SDA,PIN_I2C_SCL,I2C_FREQUENCY); // Setup I2C for Luna sensors
    frontLeftDistance = Luna(I2C_ADDRESS_LUNA_LEFT);
    frontMiddleDistance = Luna(I2C_ADDRESS_LUNA_MIDDLE);
    frontRightDistance = Luna(I2C_ADDRESS_LUNA_RIGHT);
}

void Robot::update() {
    ledRed.update();
    ledOrange.update();
}
