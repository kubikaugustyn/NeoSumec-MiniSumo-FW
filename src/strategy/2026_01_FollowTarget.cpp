//
// Created by Jakub Augustýn on 08.01.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <MainConfig.h>
#include <strategy/2026_01_FollowTarget.h>

#ifdef STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET

// machine.setState<SomeState>([](StateMachine *machine) {
//    machine->scratchRef<SomeScratch>().a = 0;
// });

void EntryState::enter() {
    Serial.println("Enter");
    robot.drive.stop();
    robot.ledRed.setOn();
    robot.ledOrange.setOff();
}

void EntryState::update() {
    // FIXME TMP
    if (machine.getStateDuration() > 5000)
        machine.setState<FollowOpponentState>();
    return;

    if (robot.startButton.get()) {
        machine.setState<SearchForOpponentState>();
    }
}

void SearchForOpponentState::update() {
    // TODO
    // robot.drive.driveStraight(0.1f); // TMP

    robot.drive.stop();
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
            middleContact = middle == 0xFFFF;

    // Serial.printf("Search: %d %d %d\n", leftOOB, middleOOB, rightOOB);

    bool lost = false;
    if (leftOOB && rightOOB && (!middleOOB || middleContact)) {
        // Serial.println("Drive forward!");
        robot.drive.driveStraight(0.5f);
    } else if (!leftOOB && rightOOB && middleOOB) {
        // Serial.println("Turn left!");
        robot.drive.turnLeft(0.5f, 1.0f);
    } else if (leftOOB && !rightOOB && middleOOB) {
        // Serial.println("Turn right!");
        robot.drive.turnRight(0.5f, 1.0f);
    } else lost = true;

    auto &data = machine.scratchRef<FollowOpponentData>();
    if (lost) {
        if (data.sightLostTime == 0) {
            Serial.println("Target lost, waiting for potential contact.");
            data.sightLostTime = machine.getStateDuration();
        } else if (machine.getStateDuration() - data.sightLostTime > CONTACT_REGAIN_TIMEOUT) {
            Serial.printf("Switching to SearchForOpponentState after %d ms of OOB.", CONTACT_REGAIN_TIMEOUT);
            machine.setState<SearchForOpponentState>();
        }
    } else
        data.sightLostTime = 0;
}

#endif // STRATEGY_NEOSUMEC_2026_01_FOLLOW_TARGET
