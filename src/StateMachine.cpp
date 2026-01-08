//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "StateMachine.h"

void StateMachine::clearState() {
    nextState = nullptr;
}

void StateMachine::update() {
    // Apply the scheduled state
    if (nextState != currentState) {
        // Exit() the current (now old) state
        // Very important: don't deallocate!!! The states are static objects at compile-time!
        if (currentState) currentState->exit();

        // Enter() the new state
        currentState = nextState;
        stateStartTime = millis();
        if (currentState) currentState->enter();
    }

    // Update() the current state
    currentStateDuration = millis() - stateStartTime;
    if (currentState) currentState->update();
}

unsigned long StateMachine::getStateDuration() const {
    return currentStateDuration;
}

State *StateMachine::getState() const {
    return currentState;
}

State *StateMachine::getNextState() const {
    return nextState;
}
