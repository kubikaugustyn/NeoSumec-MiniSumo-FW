//
// Created by Jakub Augustýn on 22.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <Preferences.h> // ESP32 persistent storage
#include "hardware/RobotState.h"

void initRobotState(StateMachine *machine) {
    auto &state = machine->sharedRef<RobotState>();
    state.tick = 5; // Some magic number so we can, for example, check for IR messages via a -1
    state.lastIRMessage = {};
    state.lastIRMessageTick = 0;

    // Init the persistent storage and load the current contents
    loadPersistentRobotState(machine);
}

void updateRobotState(StateMachine *machine) {
    auto &state = machine->sharedRef<RobotState>();
    state.tick++;
}

void loadPersistentRobotState(StateMachine *machine) {
#ifdef ROBOT_STATE_PERSISTENT_STORAGE_ENABLED
    auto &state = machine->sharedRef<RobotState>();
    Preferences preferences;
    preferences.begin("NeoSumec-rs", true);

#if START_ROBOT_TRIGGER == START_ROBOT_IR_MODULE
    state.commandIRStartStop = preferences.getUChar("IRStartStop", 0);
#endif

    preferences.end();
#endif
}

void savePersistentRobotState(StateMachine *machine) {
#ifdef ROBOT_STATE_PERSISTENT_STORAGE_ENABLED
    const auto &state = machine->sharedRef<RobotState>();
    Preferences preferences;
    preferences.begin("NeoSumec-rs", false);

#if START_ROBOT_TRIGGER == START_ROBOT_IR_MODULE
    preferences.putUChar("IRStartStop", state.commandIRStartStop);
#endif

    preferences.end();
#endif
}

void updateOnIRMessage(StateMachine *machine, const RC5Message *message) {
    auto &state = machine->sharedRef<RobotState>();
    state.lastIRMessage = *message;
    state.lastIRMessageTick = state.tick;
}
