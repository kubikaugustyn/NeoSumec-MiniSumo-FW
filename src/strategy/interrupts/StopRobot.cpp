//
// Created by Jakub Augustýn on 22.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include "strategy/interrupts/StopRobot.h"

#include "MainConfig.h"
#include "hardware/RobotState.h"
#include "strategy/debug/logging.h"

bool processStopRobotInterrupt(StateMachine *machine) {
#if START_ROBOT_TRIGGER == START_ROBOT_IR_MODULE
    // https://p1r.se/startmodule/implement-yourself/
    const auto &state = machine->sharedRef<RobotState>();
    // The fixed address used for starting and stopping the robots: 0x07
    if (state.lastIRMessage.address == 0x07) {
        // Stop command
        if (state.lastIRMessage.command == (state.commandIRStartStop & 0xFE)) {
            machine->setState<InterruptStopRobotState>();
            return true;
        }
    }
#endif

    return false;
}

void InterruptStopRobotState::enter() {
    machine.markEnteredInterrupt(InterruptCause::STOP_ROBOT);

    LOG_DEBUG_PRINTF("Stop robot interrupt: enter");

    robot.drive.stop();
    robot.ledRed.blink(100);
    robot.ledOrange.setOff();
}

void InterruptStopRobotState::update() {
    // Safety first...
    robot.drive.stop();
}
