//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#ifdef STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
#define STRATEGY_INITIAL_STATE EntryState
#define INTERRUPT_RETURN_STATE EntryState
#define LUNA_RING_THRESHOLD 60 // cm

class EntryState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override {}

    void exit() override {}
};

class SearchForOpponentState final : public BaseState {
    using BaseState::BaseState;

    void enter() override {}

    void update() override;

    void exit() override {}
};

class FollowOpponentState final : public BaseState {
    using BaseState::BaseState;

    void enter() override {}

    void update() override;

    void exit() override {}
};

#endif // STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
