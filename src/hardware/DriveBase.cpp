//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/Motion.h
//

#include "hardware/DriveBase.h"

float DriveBase::clamp(const float value, const float min, const float max) {
    return (value > max) ? max : (value < min ? min : value);
}

float DriveBase::clampNormalPositive(const float value) {
    return clamp(value, 0.0f, 1.0f);
}

float DriveBase::clampNormal(const float value) {
    return clamp(value, -1.0f, 1.0f);
}

DriveBase::DriveBase(const Motor &leftMotor, const Motor &rightMotor) {
    this->leftMotor = leftMotor;
    this->rightMotor = rightMotor;
}

void DriveBase::driveStraight(const float speed) const {
    turn(speed, 0.0f);
}

void DriveBase::turnLeft(const float turningSpeed) const {
    turn(1.0f, clampNormalPositive(turningSpeed));
}

void DriveBase::turnLeft(const float speed, const float turningSpeed) const {
    turn(speed, clampNormalPositive(turningSpeed));
}

void DriveBase::turnRight(const float turningSpeed) const {
    turn(1.0f, clampNormalPositive(turningSpeed));
}

void DriveBase::turnRight(const float speed, const float turningSpeed) const {
    turn(speed, clampNormalPositive(turningSpeed));
}

void DriveBase::turn(float speed, float turningSpeed) const {
    if (fabs(speed) < 1e-6 && fabs(turningSpeed) < 1e-6) {
        stop();
        return;
    }

    speed = clampNormal(speed);
    turningSpeed = clampNormal(turningSpeed);

    // turningSpeed > 0 = turn left
    // turningSpeed < 0 = turn right

    float d = turningSpeed * (1.0f - fabs(speed));

    leftMotor.drive(speed + d);
    rightMotor.drive(speed - d);
}

void DriveBase::turnLeftTank(float speed) const {
    speed = clampNormal(speed);

    leftMotor.drive(-speed);
    rightMotor.drive(speed);
}

void DriveBase::turnRightTank(float speed) const {
    speed = clampNormal(speed);

    leftMotor.drive(speed);
    rightMotor.drive(-speed);
}

void DriveBase::stop() const {
    leftMotor.stop();
    rightMotor.stop();
}
