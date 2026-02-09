//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "StateMachine.h"

#ifdef STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
#define STRATEGY_INITIAL_STATE EntryState
#define INTERRUPT_RETURN_STATE BackOffEdgeState
#define EDGE_BACKOFF_BACKWARDS_DURATION 200 // ms
#define LUNA_RING_THRESHOLD 70 // cm, any further means void
#define CONTACT_REGAIN_TIMEOUT 150 // ms
#define SEARCH_INITIAL_DURATION 1000 // ms
#define SEARCH_TIME_INCREMENT 500 // ms
#define SEARCH_TIME_LIMIT 5000 // ms

class EntryState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};

class BackOffEdgeState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};

struct SearchForOpponentData {
    bool turningLeft;
    unsigned long lastChangeTime;
    unsigned long turnDuration;
};

class SearchForOpponentState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};

struct FollowOpponentData {
    unsigned long sightLostTime;
    bool lastSeenLeft;
};

class FollowOpponentState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override {}
};

#endif // STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
