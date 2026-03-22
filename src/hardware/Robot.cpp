//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "hardware/Robot.h"

#include <Wire.h>

#include "hardware/Pins.h"

void Robot::begin() {
    leftMotor.begin(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL,
                    MOTOR_LEFT_SCALE);
    rightMotor.begin(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL,
                     MOTOR_RIGHT_SCALE);
    drive.begin(leftMotor, rightMotor);

    ledRed.begin(PIN_LED_RED);
    ledOrange.begin(PIN_LED_ORANGE);

    startButton.begin(PIN_BUTTON);

    lineSensorLeft.begin(PIN_QRE_LEFT);
    lineSensorRight.begin(PIN_QRE_RIGHT);
    lineSensorRear.begin(PIN_QRE_REAR);
    // FIXME Do we want this?
    // https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/37f0c36fc5ec6d57ca9154137380c8463f6ad914/main_sw/MAIN_CODE/src/main.cpp#L60-L61
    // lineSensorLeft.setThreshold(1800);
    // lineSensorRight.setThreshold(1800);

    leftProximity.begin(PIN_SHARP_LEFT);
    rightProximity.begin(PIN_SHARP_RIGHT);

    Wire.begin(PIN_I2C_SDA,PIN_I2C_SCL,I2C_FREQUENCY); // Setup I2C for Luna sensors
    frontLeftDistance.begin(I2C_ADDRESS_LUNA_LEFT);
    frontMiddleDistance.begin(I2C_ADDRESS_LUNA_MIDDLE);
    frontRightDistance.begin(I2C_ADDRESS_LUNA_RIGHT);

    // TODO Figure out the handler stuff after confirming receiving even works
    // It may be a good idea to read incoming messages in a separate interrupt (higher priority than QREs)
    infrared.begin(PIN_IR, nullptr);
}

void Robot::update() {
    ledRed.update();
    ledOrange.update();
    infrared.update();
}
