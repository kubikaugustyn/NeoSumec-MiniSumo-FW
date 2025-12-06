//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "hardware/DriveBase.h"
#include "hardware/LED.h"
#include "hardware/Motor.h"
#include "hardware/QRE.h"
#include "hardware/Sharp.h"

class Robot {
public:
    Motor leftMotor, rightMotor;
    DriveBase drive;
    LED ledRed, ledOrange;
    QRE lineSensorLeft, lineSensorRight, lineSensorRear;
    Sharp leftProximity, rightProximity;

    Robot() = default;

    void begin();
};
