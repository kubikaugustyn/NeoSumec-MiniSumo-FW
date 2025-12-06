//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "StateMachine.h"

template<typename StateType>
void StateMachine::setState() {
    static_assert(std::is_base_of<State, StateType>::value, "StateType must derive from State");

    if (currentState) currentState->exit();

    static StateType stateInstance(*this, robot);
    currentState = &stateInstance;

    stateStartTime = millis();
    currentState->enter();
}

void StateMachine::clearState() {
    if (!currentState) return;

    currentState->exit();
    stateStartTime = millis();
    currentState = nullptr;
}

void StateMachine::update() {
    if (currentState) currentState->update();
    currentStateDuration = millis() - stateStartTime;
}

unsigned long StateMachine::getStateDuration() const {
    return currentStateDuration;
}

State *StateMachine::getState() const {
    return currentState;
}
