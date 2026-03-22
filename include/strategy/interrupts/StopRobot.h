//
// Created by Jakub Augustýn on 22.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

bool processStopRobotInterrupt(StateMachine *machine);

class InterruptStopRobotState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};
