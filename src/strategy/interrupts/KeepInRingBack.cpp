//
// Created by Jakub Augustýn on 10.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/KeepInRingBack.h"
#include "strategy/interrupts/interrupts.h"

#ifndef INTERRUPT_KEEP_IN_RING_DISABLE

bool processKeepInRingBackInterrupt(StateMachine *machine) {
    const auto robot = machine->getRobot();
    if (robot.lineSensorRear.get()) {
        machine->setState<InterruptKeepInRingBackState>();
        return true;
    }

    return false;
}

void InterruptKeepInRingBackState::enter() {
    machine.markEnteredInterrupt(InterruptCause::REAR_QRE);

    robot.drive.driveStraight(1.0f);
}

void InterruptKeepInRingBackState::update() {
    if (robot.lineSensorRear.get()) return;
    machine.setState<INTERRUPT_RETURN_STATE>();
}

void InterruptKeepInRingBackState::exit() {
    machine.markExitedInterrupt();
}

#endif // INTERRUPT_KEEP_IN_RING_DISABLE
