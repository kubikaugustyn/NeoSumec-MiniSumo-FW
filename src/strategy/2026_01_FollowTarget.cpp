//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <MainConfig.h>
#include <strategy/2026_01_FollowTarget.h>

#include "strategy/debug/logging.h"
#include "strategy/interrupts/interrupts.h"

#ifdef STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET

// machine.setState<SomeState>([](StateMachine *machine) {
//    machine->scratchRef<SomeScratch>().a = 0;
// });

void EntryState::enter() {
    Serial.println("Enter");
    robot.drive.driveStraight(1.0f);
}

void EntryState::update() {
    if (machine.getStateDuration() < 300) return;
    machine.setState<SearchForOpponentState>();
}

void BackOffEdgeState::enter() {
    const auto &data = machine.scratchRef<InterruptResultData>();
    if (data.cause != InterruptCause::LEFT_QRE && data.cause != InterruptCause::RIGHT_QRE) {
        machine.setState<SearchForOpponentState>();
        return;
    }

    robot.drive.driveStraight(-1.0f);
}

void BackOffEdgeState::update() {
    if (machine.getStateDuration() < EDGE_BACKOFF_BACKWARDS_DURATION) return;
    machine.setState<SearchForOpponentState>();
}

void SearchForOpponentState::enter() {
    auto &data = machine.scratchRef<SearchForOpponentData>();
    // Will be flipped to get the first direction
    // Btw it can be overridden by a callback provided to setState()
    data.turningLeft = false;
    data.lastChangeTime = 0;
    data.turnDuration = 0;
    robot.ledRed.setOn();
    robot.ledOrange.blink(100);
}

void SearchForOpponentState::update() {
    // Exit condition
    if (robot.frontMiddleDistance.getRaw() <= LUNA_RING_THRESHOLD) {
        machine.setState<FollowOpponentState>();
        return;
    }

    // Change the direction
    auto &data = machine.scratchRef<SearchForOpponentData>();
    if (machine.getStateDuration() - data.lastChangeTime >= data.turnDuration) {
        data.turningLeft = !data.turningLeft;
        data.lastChangeTime = machine.getStateDuration();
        if (data.turnDuration == 0) data.turnDuration = SEARCH_INITIAL_DURATION;
        else if (data.turningLeft && data.turnDuration < SEARCH_TIME_LIMIT) data.turnDuration += SEARCH_TIME_INCREMENT;

        if (data.turningLeft) robot.drive.turnLeftTank(1.0f);
        else robot.drive.turnRightTank(1.0f);
    }
}

void FollowOpponentState::enter() {
    machine.scratchRef<FollowOpponentData>().sightLostTime = 0;
    robot.ledRed.blink(100);
    robot.ledOrange.setOn();
}

void FollowOpponentState::update() {
    const uint16_t left = robot.frontLeftDistance.getRaw(),
            middle = robot.frontMiddleDistance.getRaw(),
            right = robot.frontRightDistance.getRaw();
    const bool leftOOB = left > LUNA_RING_THRESHOLD,
            middleOOB = middle > LUNA_RING_THRESHOLD,
            rightOOB = right > LUNA_RING_THRESHOLD,
            leftContact = left == 0xFFFF,
            middleContact = middle == 0xFFFF,
            rightContact = right == 0xFFFF;

    // LOG_DEBUG_PRINTF("Search: %d %d %d\n", left, middle, right);
    LOG_DEBUG_PRINTF("Search: %d %d %d", leftOOB, middleOOB, rightOOB);

    auto &data = machine.scratchRef<FollowOpponentData>();
    bool lost = false;
    if ((leftOOB && rightOOB && !middleOOB) || middleContact) {
        LOG_DEBUG_PRINTF("Drive forward!");
        robot.drive.driveStraight(1.0f);
    } else if ((!leftOOB && rightOOB) || leftContact) {
        LOG_DEBUG_PRINTF("Turn left!");
        robot.drive.turnLeft(1.0f, 0.5f);
        data.lastSeenLeft = true;
    } else if ((leftOOB && !rightOOB) || rightContact) {
        LOG_DEBUG_PRINTF("Turn right!");
        robot.drive.turnRight(1.0f, 0.5f);
        data.lastSeenLeft = false;
    } else lost = true;

    if (lost) {
        if (data.sightLostTime == 0) {
            LOG_DEBUG_PRINTF("Target lost, waiting for potential contact.");
            data.sightLostTime = machine.getStateDuration();
            // FIXME Don't do that, as every ms could mean a win or a loss
            // But idk... it fixes it too
            robot.drive.stop();
        } else if (machine.getStateDuration() - data.sightLostTime > CONTACT_REGAIN_TIMEOUT) {
            LOG_DEBUG_PRINTF("Switching to SearchForOpponentState after %d ms of OOB.", CONTACT_REGAIN_TIMEOUT);
            // Remember that the initial turning direction is negated
            // I hate stateless lambdas :-/
            if (data.lastSeenLeft) {
                // Search to the left
                machine.setState<SearchForOpponentState>([](StateMachine *m) {
                    m->scratchRef<SearchForOpponentData>().turningLeft = false;
                });
            } else {
                // Search to the right
                machine.setState<SearchForOpponentState>([](StateMachine *m) {
                    m->scratchRef<SearchForOpponentData>().turningLeft = true;
                });
            }
        }
    } else
        data.sightLostTime = 0;
}

#endif // STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
