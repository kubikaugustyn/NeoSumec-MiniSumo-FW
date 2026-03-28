//
// Created by Jakub Augustýn on 28.03.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#ifdef STRATEGY_NEOSUMEC_2026_03_ROBO_STRONG
#define STRATEGY_INITIAL_STATE RoboStrongState
#define INTERRUPT_RETURN_STATE RoboStrongState

class RoboStrongState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override {};

    void exit() override {};
};

#endif // STRATEGY_NEOSUMEC_2026_03_ROBO_STRONG
