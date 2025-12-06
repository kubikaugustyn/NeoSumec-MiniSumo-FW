//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#include "StateMachine.h"

template<typename T>
StateMachine<T>::StateMachine(T initialState) {
    setState(initialState);
}

template<typename T>
void StateMachine<T>::setState(T newState) {
    currentState = newState;
    stateStartTime = millis();
}

template<typename T>
T StateMachine<T>::getState() const {
    return currentState;
}

template<typename T>
unsigned long StateMachine<T>::getStateDuration() const {
    return millis() - stateStartTime;
}

template<typename T>
void StateMachine<T>::update() {
    // Future debug or other things
}

// Explicit instantiation for RobotState
#include "RobotState.h"
template class StateMachine<RobotState>;
