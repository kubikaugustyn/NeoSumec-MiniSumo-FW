//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "RobotState.h"

// #define DEBUG_SPEED_SCALING 0.5f
// #define DEBUG_TIME_SCALING 2
#define DEBUG_SPEED_SCALING 1.0f
#define DEBUG_TIME_SCALING 1

void DriveForwardState::enter() {
    robot.drive.driveStraight(1.0f * DEBUG_SPEED_SCALING);
}

void DriveForwardState::update() {
    if (robot.lineSensorLeft.get() || robot.lineSensorRight.get() || robot.lineSensorRear.get()) {
        machine.setState<DriveBackwardState>();
    }
}


void DriveBackwardState::enter() {
    robot.drive.driveStraight(-1.0f * DEBUG_SPEED_SCALING);
}

void DriveBackwardState::update() {
    if (machine.getStateDuration() > 100 * DEBUG_TIME_SCALING) {
        machine.setState<TurnState>();
    }
}


void TurnState::enter() {
    robot.drive.turnRightTank(1.0f * DEBUG_SPEED_SCALING);
}

void TurnState::update() {
    if (machine.getStateDuration() > 300 * DEBUG_TIME_SCALING) {
        machine.setState<DriveForwardState>();
    }
}
