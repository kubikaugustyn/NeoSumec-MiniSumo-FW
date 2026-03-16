//
// Created by Jakub Augustýn at 05.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <Arduino.h>

#include "MainConfig.h"
#include "StateMachine.h"
#include "strategy/debug/logging.h"
#include "strategy/interrupts/StartRobot.h"

auto robot = Robot();
auto state = StateMachine(robot);

void setup() {
#if LOG_LEVEL > LOGGING_DISABLED
    Serial.begin(115200);
#endif
    robot.begin();

    // Set the first state
    state.setState<InterruptStartRobotState>();
}

void loop() {
#if LOG_LEVEL >= LOG_DEBUG
    uint64_t sTime = millis();
#endif

    // Update the hardware
    robot.update();
    // Update the state/strategy
    state.update();

#if LOG_LEVEL >= LOG_DEBUG
    uint64_t eTime = millis();
    LOG_DEBUG_PRINTF("Loop took %d ms", eTime - sTime);
#endif
}