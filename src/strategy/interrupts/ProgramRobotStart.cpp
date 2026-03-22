//
// Created by Jakub Augustýn on 22.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/ProgramRobotStart.h"

void InterruptProgramRobotStartState::enter() {
    robot.ledOrange.setOff();
    robot.ledRed.blink(250); // 2 blinks per second
}

void InterruptProgramRobotStartState::update() {
    if (machine.getStateDuration() < 1000) return;

    machine.setState<InterruptStartRobotState>();
}
