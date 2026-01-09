//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// AI slop ahead, don't read!!!

#include <MainConfig.h>
#include <strategy/2025_02_FollowTarget.h>

#ifdef STRATEGY_NEOSUMEC_2025_02_FOLLOW_TARGET

void EntryState::enter() {
    // Intended for also being able to prepare the scratch memory first. It may be a good idea to somehow make the scratch system more robust, such as requiring a callback that would write to the scratch for the setState method for certain states? I'm not sure, we don't want to waste memory though.
    machine.setState<FollowOpponentState>();
}

// AI slop ahead, don't read!!!

void SearchForOpponentState::update() {
    auto &scratch = machine.scratchRef<FollowScratch>();

    const uint16_t left = robot.frontLeftDistance.getRaw();
    const uint16_t middle = robot.frontMiddleDistance.getRaw();
    const uint16_t right = robot.frontRightDistance.getRaw();

    // Pokud sensor failnul, čekáme
    if (left == 0xFFFF || middle == 0xFFFF || right == 0xFFFF)
        return;

    const bool targetVisible =
            (left < LUNA_RING_THRESHOLD || middle < LUNA_RING_THRESHOLD || right < LUNA_RING_THRESHOLD);

    if (targetVisible) {
        // Uložíme poslední známou polohu
        if (left < LUNA_RING_THRESHOLD && right < LUNA_RING_THRESHOLD)
            scratch.targetLastSeenOnTheLeft = (left < right);
        else if (left < LUNA_RING_THRESHOLD)
            scratch.targetLastSeenOnTheLeft = true;
        else
            scratch.targetLastSeenOnTheLeft = false;

        machine.setState<FollowOpponentState>();
        return;
    }

    // Pokud cíl není vidět, točíme se jen jedním příkazem
    robot.drive.turnLeftTank(0.3f);
}

void FollowOpponentState::update() {
    auto &scratch = machine.scratchRef<FollowScratch>();

    // Čteme Luny
    const uint16_t left = robot.frontLeftDistance.getRaw();
    const uint16_t middle = robot.frontMiddleDistance.getRaw();
    const uint16_t right = robot.frontRightDistance.getRaw();

    // Pokud sensor failnul, počkej na další update
    if (left == 0xFFFF || middle == 0xFFFF || right == 0xFFFF)
        return;

    // Zkontrolovat, jestli je cíl stále vidět podle LUNA_RING_THRESHOLD
    const bool targetVisible =
            (left < LUNA_RING_THRESHOLD || middle < LUNA_RING_THRESHOLD || right < LUNA_RING_THRESHOLD);

    if (!targetVisible) {
        robot.drive.stop();
        machine.setState<SearchForOpponentState>();
        return;
    }

    // Rozhodnutí podle Lun
    bool targetLeft = scratch.targetLastSeenOnTheLeft;

    if (left < LUNA_RING_THRESHOLD && right < LUNA_RING_THRESHOLD)
        targetLeft = (left < right);
    else if (left < LUNA_RING_THRESHOLD)
        targetLeft = true;
    else if (right < LUNA_RING_THRESHOLD)
        targetLeft = false;

    scratch.targetLastSeenOnTheLeft = targetLeft;

    // Tank turn podle směru, voláme drive jen jednou
    if (middle < 50) {
        // threshold blízko cíle
        robot.drive.stop();
    } else if (targetLeft) {
        robot.drive.turnLeftTank(0.4f);
    } else {
        robot.drive.turnRightTank(0.4f);
    }

    // Uložíme poslední vzdálenost
    scratch.lastDistance = middle;
    scratch.previousLeftRight = targetLeft;
}

#endif // STRATEGY_NEOSUMEC_2025_02_FOLLOW_TARGET
