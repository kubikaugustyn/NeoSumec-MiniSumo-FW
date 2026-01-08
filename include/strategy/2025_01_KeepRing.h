//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#ifdef STRATEGY_NEOSUMEC_2025_01_KEEP_RING
#define STRATEGY_INITIAL_STATE DriveForwardState

class DriveForwardState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {};
};

class DriveBackwardState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {};
};

class TurnState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {};
};

#endif // STRATEGY_NEOSUMEC_2025_01_KEEP_RING
