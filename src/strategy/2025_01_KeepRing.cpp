//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <MainConfig.h>
#include <strategy/2025_01_KeepRing.h>

#ifdef STRATEGY_NEOSUMEC_2025_01_KEEP_RING

// We must define all the possible states for the compiler

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
    if (machine.getStateDuration() > 100) {
        machine.setState<TurnState>();
    }
}


void TurnState::enter() {
    robot.drive.turnRightTank(1.0f);
}

void TurnState::update() {
    if (machine.getStateDuration() > 300) {
        machine.setState<DriveForwardState>();
    }
}

#endif // STRATEGY_NEOSUMEC_2025_01_KEEP_RING
