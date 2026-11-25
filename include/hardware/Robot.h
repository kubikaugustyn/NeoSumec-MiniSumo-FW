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
#include "hardware/Luna.h"
#include "hardware/Lidar.h"
#include "hardware/RC5Receiver.h"
#include "hardware/Button.h"
// TODO Adding this include breaks compilation, probably as a result of some sort of circular import / import order error. It is required to build code for robots with the Luna sensors.
// #include "hardware/Pins.h" // Required to load the Luna pins

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
    Luna frontMiddleDistance;
#ifdef I2C_ADDRESS_LUNA_LEFT
    Luna frontLeftDistance;
#else
    Lidar frontLeftDistance;
#endif
#ifdef I2C_ADDRESS_LUNA_RIGHT
    Luna frontRightDistance;
#else
    Lidar frontRightDistance;
#endif
    // IR RC-5 receiver
    RC5Receiver infrared;

    Robot() = default;

    void begin();

    void update();
};
