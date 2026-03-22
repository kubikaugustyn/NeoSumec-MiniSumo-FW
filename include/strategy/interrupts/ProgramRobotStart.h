//
// Created by Jakub Augustýn on 22.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#include "MainConfig.h"
#include "strategy/interrupts/StartRobot.h"

#if START_ROBOT_TRIGGER == START_ROBOT_IR_MODULE
class InterruptProgramRobotStartState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};
#endif