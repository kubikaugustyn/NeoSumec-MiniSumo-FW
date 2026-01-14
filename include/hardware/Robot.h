//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "Button.h"
#include "hardware/DriveBase.h"
#include "hardware/LED.h"
#include "hardware/Motor.h"
#include "hardware/QRE.h"
#include "hardware/Sharp.h"
#include "hardware/Luna.h"

class Robot {
public:
    Motor leftMotor, rightMotor;
    DriveBase drive;
    LED ledRed, ledOrange;
    Button startButton;
    // QRE bottom line sensors
    QRE lineSensorLeft, lineSensorRight, lineSensorRear;
    // Sharp side proximity sensors
    Sharp leftProximity, rightProximity;
    // Luna frontal distance sensors
    Luna frontLeftDistance, frontMiddleDistance, frontRightDistance;

    Robot() = default;

    void begin();

    void update();
};
