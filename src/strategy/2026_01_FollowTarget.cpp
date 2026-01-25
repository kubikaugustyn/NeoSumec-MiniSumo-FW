//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <MainConfig.h>
#include <strategy/2026_01_FollowTarget.h>

#include "strategy/interrupts/interrupts.h"

#ifdef STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET

// machine.setState<SomeState>([](StateMachine *machine) {
//    machine->scratchRef<SomeScratch>().a = 0;
// });

bool MOVE = true; // FIXME Tmp

void EntryState::enter() {
    Serial.println("Enter");
    if (MOVE) robot.drive.driveStraight(1.0f);
}

void EntryState::update() {
    if (machine.getStateDuration() < 300) return;
    machine.setState<SearchForOpponentState>();
    if (!MOVE) machine.setState<FollowOpponentState>();
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
    data.turningLeft = true;
    data.lastChangeTime = 0;
    data.turnDuration = 0;
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

    // Serial.printf("Search: %d %d %d\n", left, middle, right);
    Serial.printf("Search: %d %d %d\n", leftOOB, middleOOB, rightOOB);

    bool lost = false;
    if ((leftOOB && rightOOB && !middleOOB) || middleContact) {
        Serial.println("Drive forward!");
        if (MOVE) robot.drive.driveStraight(1.0f);
    } else if ((!leftOOB && rightOOB) || leftContact) {
        Serial.println("Turn left!");
        if (MOVE) robot.drive.turnLeft(1.0f, 1.0f);
    } else if ((leftOOB && !rightOOB) || rightContact) {
        Serial.println("Turn right!");
        if (MOVE) robot.drive.turnRight(1.0f, 1.0f);
    } else lost = true;

    auto &data = machine.scratchRef<FollowOpponentData>();
    if (lost) {
        if (data.sightLostTime == 0) {
            Serial.println("Target lost, waiting for potential contact.");
            data.sightLostTime = machine.getStateDuration();
            // FIXME Don't do that, as every ms could mean a win or a loss
            // But idk... it fixes it too
            robot.drive.stop();
        } else if (machine.getStateDuration() - data.sightLostTime > CONTACT_REGAIN_TIMEOUT) {
            Serial.printf("Switching to SearchForOpponentState after %d ms of OOB.\n", CONTACT_REGAIN_TIMEOUT);
            if (MOVE) machine.setState<SearchForOpponentState>();
        }
    } else
        data.sightLostTime = 0;
}

#endif // STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
