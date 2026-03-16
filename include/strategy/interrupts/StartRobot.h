//
// Created by Jakub Augustýn on 21.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#define START_ROBOT_BUTTON 1
#define START_ROBOT_IR_MODULE 2 // https://p1r.se/startmodule/

class InterruptStartRobotState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};

class InterruptStartRobotWaitState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override;
};
