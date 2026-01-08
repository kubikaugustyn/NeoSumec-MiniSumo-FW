//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#ifdef STRATEGY_NEOSUMEC_2025_02_FOLLOW_TARGET
#define STRATEGY_INITIAL_STATE EntryState
#define LUNA_RING_THRESHOLD 60 // cm

class EntryState : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override {}

    void exit() override {}
};

struct FollowScratch {
    bool targetLastSeenOnTheLeft = true;  // poslední poloha cíle
    uint16_t lastDistance = 0;            // poslední vzdálenost k cíli
    bool previousLeftRight = true;        // směr, kterým se cíl pohyboval naposledy
};

class SearchForOpponentState : public BaseState {
    using BaseState::BaseState;

    void enter() override {}

    void update() override;

    void exit() override {}
};

class FollowOpponentState : public BaseState {
    using BaseState::BaseState;

    void enter() override {}

    void update() override;

    void exit() override {}
};

#endif // STRATEGY_NEOSUMEC_2025_02_FOLLOW_TARGET
