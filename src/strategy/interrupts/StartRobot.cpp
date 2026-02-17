//
// Created by Jakub Augustýn on 21.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/StartRobot.h"

#include "strategy/debug/logging.h"
#include "strategy/interrupts/interrupts.h"

void InterruptStartRobotState::enter() {
    machine.markEnteredInterrupt(InterruptCause::START_ROBOT);

    LOG_DEBUG_PRINTF("Start robot interrupt: enter");

    robot.drive.stop();
    robot.ledRed.setOn();
    robot.ledOrange.setOff();
}

void InterruptStartRobotState::update() {
    if (!robot.startButton.get()) return;
    machine.setState<InterruptStartRobotWaitState>();
}

void InterruptStartRobotWaitState::enter() {
    LOG_DEBUG_PRINTF("Start robot interrupt: button pressed");

    robot.ledRed.setOff();
    robot.ledOrange.setOn();
}

void InterruptStartRobotWaitState::update() {
    if (machine.getStateDuration() < START_BUTTON_DELAY) return;

    LOG_DEBUG_PRINTF("Start robot interrupt: starting strategy...");
    machine.setState<STRATEGY_INITIAL_STATE>();
}

void InterruptStartRobotWaitState::exit() {
    machine.markExitedInterrupt();
}
