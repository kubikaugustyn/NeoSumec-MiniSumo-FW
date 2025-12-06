//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "hardware/Robot.h"
#include "hardware/Pins.h"

void Robot::begin() {
    leftMotor = Motor(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL);
    rightMotor = Motor(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL);
    drive = DriveBase(leftMotor, rightMotor);

    ledRed = LED(PIN_LED_RED);
    ledOrange = LED(PIN_LED_ORANGE);

    lineSensorLeft = QRE(PIN_QRE_LEFT);
    lineSensorRight = QRE(PIN_QRE_RIGHT);
    lineSensorRear = QRE(PIN_QRE_REAR);

    leftProximity = Sharp(PIN_SHARP_LEFT);
    rightProximity = Sharp(PIN_SHARP_RIGHT);
}

void Robot::update() {
    ledRed.update();
    ledOrange.update();
}
