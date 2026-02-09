//
// Created by Jakub Augustýn on 09.02.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#ifdef STRATEGY_NEOSUMEC_2026_02_TEST_TURNING
#define STRATEGY_INITIAL_STATE TurnLeftState
#define INTERRUPT_RETURN_STATE TurnLeftState
#define TURNING_STATE_DURATION 500

class TurnLeftState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};

class TurnRightState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};

#endif // STRATEGY_NEOSUMEC_2026_02_TEST_TURNING
