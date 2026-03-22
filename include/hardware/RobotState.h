//
// Created by Jakub Augustýn on 22.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"
#include "hardware/RC5Receiver.h"
#include "MainConfig.h"
#include "strategy/interrupts/StartRobot.h"

#if START_ROBOT_TRIGGER == START_ROBOT_IR_MODULE
#define ROBOT_STATE_PERSISTENT_STORAGE_ENABLED
#endif

struct RobotState {
    uint64_t tick;
    RC5Message lastIRMessage;
    uint64_t lastIRMessageTick;

    // Persistent data storage
#ifdef ROBOT_STATE_PERSISTENT_STORAGE_ENABLED
#if START_ROBOT_TRIGGER == START_ROBOT_IR_MODULE
    uint8_t commandIRStartStop; // Start command = startStop | 1, stop command = startStop & 0xFE
#endif
#endif
};

void initRobotState(StateMachine *machine);

void updateRobotState(StateMachine *machine);

void loadPersistentRobotState(StateMachine *machine);

void savePersistentRobotState(StateMachine *machine);

void updateOnIRMessage(StateMachine *machine, const RC5Message *message);
