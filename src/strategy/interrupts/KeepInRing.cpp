//
// Created by Jakub Augustýn on 10.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/KeepInRing.h"

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
    if (robot.lineSensorLeft.get() || robot.lineSensorRight.get()) return;
    machine.setState<INTERRUPT_RETURN_STATE>();
}

void InterruptKeepInRingState::exit() {
    machine.markExitedInterrupt();
}

#endif // INTERRUPT_KEEP_IN_RING_DISABLE
