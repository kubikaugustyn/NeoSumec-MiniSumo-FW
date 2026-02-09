//
// Created by Jakub Augustýn on 09.02.2026.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <MainConfig.h>
#include <strategy/2026_02_TestTurning.h>

#ifdef STRATEGY_NEOSUMEC_2026_02_TEST_TURNING

void TurnLeftState::enter() {
    robot.drive.turnLeft(1.0f);
    robot.ledOrange.setOn();
    robot.ledRed.setOff();
}

void TurnRightState::enter() {
    robot.drive.turnRight(1.0f);
    robot.ledOrange.setOff();
    robot.ledRed.setOn();
}

void TurnLeftState::update() {
    if (machine.getStateDuration() < TURNING_STATE_DURATION) return;
    machine.setState<TurnRightState>();
}

void TurnRightState::update() {
    if (machine.getStateDuration() < TURNING_STATE_DURATION) return;
    machine.setState<TurnLeftState>();
}

#endif // STRATEGY_NEOSUMEC_2026_02_TEST_TURNING
