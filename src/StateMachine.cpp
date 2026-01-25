//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "StateMachine.h"
#include "strategy/interrupts/interrupts.h"

void StateMachine::markEnteredInterrupt(const InterruptCause cause) {
    enableInterrupts = false;

    // Save the information about the interrupt
    auto &data = scratchRef<InterruptResultData>();
    data.cause = cause;
}

void StateMachine::markExitedInterrupt() {
    enableInterrupts = true;
}

void StateMachine::clearState() {
    nextState = nullptr;
    nextStateCallback = nullptr;
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
        if (nextStateCallback) {
            nextStateCallback(this);
            nextStateCallback = nullptr;
        }
    }

    // Check for interrupts
    if (enableInterrupts && processInterrupts(this)) {
        // Some interrupt called setState(). Immediately exit and wait for the next `update()` call.
#ifdef DEBUG_LOGGING
        Serial.println("StateMachine::update(): Received interrupt.");
#endif
        return;
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
