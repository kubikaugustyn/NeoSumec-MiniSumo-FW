//
// Created by Jakub Augustýn on 21.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/StartRobot.h"

#include "hardware/RobotState.h"
#include "strategy/interrupts/interrupts.h"
#include "MainConfig.h"
#include "strategy/debug/logging.h"
#include "strategy/interrupts/ProgramRobotStart.h"
#include "strategy/interrupts/StopRobot.h"

void InterruptStartRobotState::enter() {
    machine.markEnteredInterrupt(InterruptCause::START_ROBOT);

    LOG_DEBUG_PRINTF("Start robot interrupt: enter");

    robot.drive.stop();
    robot.ledRed.setOn();
    robot.ledOrange.setOff();
}

void InterruptStartRobotState::update() {
#if START_ROBOT_TRIGGER == START_ROBOT_BUTTON
    if (!robot.startButton.get()) return;
    machine.setState<InterruptStartRobotWaitState>();
#elif START_ROBOT_TRIGGER == START_ROBOT_IR_MODULE
    // https://p1r.se/startmodule/implement-yourself/
    auto &state = machine.sharedRef<RobotState>();
    if (state.lastIRMessageTick != state.tick - 1) return;
    // The fixed address used for programming: 0x0B
    if (state.lastIRMessage.address == 0x0B) {
        state.commandIRStartStop = state.lastIRMessage.command & 0xFE;
        savePersistentRobotState(&machine);

        // Play the animation
        machine.setState<InterruptProgramRobotStartState>();
        return;
    }
    // The fixed address used for starting and stopping the robots: 0x07
    if (state.lastIRMessage.address == 0x07) {
        // Start command
        if (state.lastIRMessage.command == (state.commandIRStartStop | 1)) {
            machine.setState<InterruptStartRobotWaitState>();
            return;
        }
        // Stop command
        else if (state.lastIRMessage.command == (state.commandIRStartStop & 0xFE)) {
            machine.setState<InterruptStopRobotState>();
            return;
        }
        // else: Different command "ID"
    }
#endif
}

void InterruptStartRobotWaitState::enter() {
    LOG_DEBUG_PRINTF("Start robot interrupt: started, waiting...");

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
