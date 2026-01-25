//
// Created by Jakub Augustýn on 10.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/KeepInRing.h"
#include "strategy/interrupts/interrupts.h"
#include "strategy/interrupts/KeepInRingBack.h"

#ifndef INTERRUPT_KEEP_IN_RING_DISABLE

bool processKeepInRingInterrupt(StateMachine *machine) {
    const auto robot = machine->getRobot();
    if (robot.lineSensorLeft.get() || robot.lineSensorRight.get()) {
        machine->setState<InterruptKeepInRingState>();
        return true;
    }

    return false;
}

void InterruptKeepInRingState::enter() {
    machine.markEnteredInterrupt(robot.lineSensorLeft.get() ? InterruptCause::LEFT_QRE : InterruptCause::RIGHT_QRE);

    robot.drive.driveStraight(-1.0f);
}

void InterruptKeepInRingState::update() {
    // NEVER EVER drive backwards outside the ring
    if (robot.lineSensorRear.get()) {
        machine.setState<InterruptKeepInRingBackState>();
        return;
    }

    // Drive backwards
    if (robot.lineSensorLeft.get() || robot.lineSensorRight.get()) {
        robot.drive.driveStraight(-1.0f);
        return;
    }

    // Turn away from the line
    if (machine.scratchRef<InterruptResultData>().cause == InterruptCause::LEFT_QRE)
        robot.drive.turnRightTank(1.0f);
    else
        robot.drive.turnLeftTank(1.0f);

    // Done
    if (machine.getStateDuration() < 500) return;
    machine.setState<INTERRUPT_RETURN_STATE>();
}

void InterruptKeepInRingState::exit() {
    machine.markExitedInterrupt();
}

#endif // INTERRUPT_KEEP_IN_RING_DISABLE
