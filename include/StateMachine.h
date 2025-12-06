//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include <Arduino.h>

template<typename T>
class StateMachine {
private:
    T currentState;
    unsigned long stateStartTime;

public:
    StateMachine() = default;

    explicit StateMachine(T initialState);

    void setState(T newState);

    T getState() const;

    unsigned long getStateDuration() const;

    void update();
};
