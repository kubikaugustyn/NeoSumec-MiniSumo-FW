//
// Created by Jakub Augustýn on 06.12.2025.
// Copyright (c) 2025 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

class BaseState : public State {
public:
    BaseState(StateMachine &m, Robot &r) : State(m, r) {
    }
};

class DriveForwardState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;
};

class DriveBackwardState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;
};

class TurnState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;
};
