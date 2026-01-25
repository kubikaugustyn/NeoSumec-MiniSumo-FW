//
// Created by Jakub Augustýn on 10.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#pragma once
#include "MainConfig.h" // Don't remove!
#include "StateMachine.h"

#ifndef INTERRUPT_KEEP_IN_RING_DISABLE

bool processKeepInRingFrontInterrupt(StateMachine *machine);

class InterruptKeepInRingFrontState final : public BaseState {
    using BaseState::BaseState;

    void enter() override;

    void update() override;

    void exit() override;
};

#endif // INTERRUPT_KEEP_IN_RING_DISABLE