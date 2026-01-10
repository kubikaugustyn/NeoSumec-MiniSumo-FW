//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <MainConfig.h>
#include <strategy/2026_01_FollowTarget.h>

#ifdef STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET

void EntryState::enter() {
    machine.setState<FollowOpponentState>();
    // machine.setState<FollowOpponentState>([](StateMachine *machine) {
    //    machine->scratchRef<SomeScratch>().a = 0;
    // });
}

void SearchForOpponentState::update() {
    // TODO
}

void FollowOpponentState::update() {
    // TODO
}

#endif // STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
