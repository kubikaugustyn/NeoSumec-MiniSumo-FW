//
// Created by Jakub Augustýn on 21.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/StartRobot.h"
#include "strategy/interrupts/interrupts.h"

void InterruptStartRobotState::enter() {
    machine.markEnteredInterrupt(InterruptCause::START_ROBOT);

#ifdef DEBUG_LOGGING
    Serial.println("Start robot interrupt: enter");
#endif

    robot.drive.stop();
    robot.ledRed.setOn();
    robot.ledOrange.setOff();
}

void InterruptStartRobotState::update() {
    if (!robot.startButton.get()) return;
    machine.setState<InterruptStartRobotWaitState>();
}

void InterruptStartRobotWaitState::enter() {
#ifdef DEBUG_LOGGING
    Serial.println("Start robot interrupt: button pressed");
#endif

    robot.ledRed.setOff();
    robot.ledOrange.setOn();
}

void InterruptStartRobotWaitState::update() {
    if (machine.getStateDuration() < START_BUTTON_DELAY) return;
    machine.setState<STRATEGY_INITIAL_STATE>();
}

void InterruptStartRobotWaitState::exit() {
    machine.markExitedInterrupt();
}
