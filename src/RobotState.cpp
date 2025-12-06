//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "RobotState.h"

void DriveForwardState::enter() {
    robot.drive.driveStraight(1.0f);
}

void DriveForwardState::update() {
    if (robot.lineSensorLeft.get() || robot.lineSensorRight.get() || robot.lineSensorRear.get()) {
        machine.setState<DriveBackwardState>();
    }
}


void DriveBackwardState::enter() {
    robot.drive.driveStraight(-1.0f);
}

void DriveBackwardState::update() {
    if (machine.getStateDuration() > 500) {
        machine.setState<TurnState>();
    }
}


void TurnState::enter() {
    robot.drive.turnLeft(1.0f);
}

void TurnState::update() {
    if (machine.getStateDuration() > 500) {
        machine.setState<DriveForwardState>();
    }
}
