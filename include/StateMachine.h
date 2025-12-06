//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "hardware/Robot.h"

//---------------- State Forward Declaration ----------------
class StateMachine;

//---------------- Abstract State Class ----------------
class State {
protected:
    StateMachine &machine;
    Robot &robot;

    State(StateMachine &m, Robot &r) : machine(m), robot(r) {
    }

public:
    State() = delete;

    virtual ~State() = default;

    virtual void enter() = 0;

    virtual void update() = 0;

    virtual void exit() = 0;
};

//---------------- State Machine ----------------
class StateMachine {
    Robot &robot;
    State *currentState = nullptr;
    unsigned long stateStartTime = 0, currentStateDuration = 0;

public:
    StateMachine() = delete;

    explicit StateMachine(Robot &r) : robot(r) {
    }

    template<typename StateType>
    void setState();

    void clearState();

    void update();

    unsigned long getStateDuration() const;

    State *getState() const;
};
