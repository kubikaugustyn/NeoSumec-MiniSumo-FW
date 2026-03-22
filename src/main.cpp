//
// Created by Jakub Augustýn at 05.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <Arduino.h>

#include "MainConfig.h"
#include "StateMachine.h"
#include "callbacks.h"
#include "hardware/RobotState.h"
#include "strategy/debug/logging.h"
#include "strategy/interrupts/StartRobot.h"

Robot robot;
auto state = StateMachine(robot);

void setup() {
#if LOG_LEVEL > LOGGING_DISABLED
    Serial.begin(115200);
    delay(5000);
    LOG_INFO_PRINT(F("NeoSumec by Jakub Augystyn, " __FILE__ " from " __DATE__));
#endif
    robot.begin();

    // Set the first state
    initRobotState(&state);
    state.setState<InterruptStartRobotState>();
}

void loop() {
#if LOG_LEVEL >= LOG_DEBUG && defined(DEBUG_ENABLE_TIMING)
    uint64_t sTime = millis();
#endif

    // Update the hardware
    robot.update();
    // Update the state/strategy
    updateRobotState(&state);
    state.update();

#if LOG_LEVEL >= LOG_DEBUG && defined(DEBUG_ENABLE_TIMING)
    uint64_t eTime = millis();
    LOG_DEBUG_PRINTF("Loop took %llu ms", eTime - sTime);
#endif
}

// Implement C-style callbacks
void onIRMessage(const RC5Message *message) {
    updateOnIRMessage(&state, message);
}
