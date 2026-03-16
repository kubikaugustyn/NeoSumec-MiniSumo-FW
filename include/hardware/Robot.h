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
#include "hardware/RC5Receiver.h"

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
    // IR RC-5 receiver
    RC5Receiver infrared;

    Robot() = default;

    void begin();

    void update();
};
