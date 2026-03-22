//
// Created by Jakub Augustýn at 05.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <Arduino.h>

#include "MainConfig.h"
#include "StateMachine.h"
#include "strategy/debug/logging.h"
#include "strategy/interrupts/StartRobot.h"

Robot robot;
auto state = StateMachine(robot);

void setup() {
#if LOG_LEVEL > LOGGING_DISABLED
    Serial.begin(115200);
    delay(5000);
    LOG_INFO_PRINT(F("NeoSumec by Jakub Augystyn, " __FILE__ " from " __DATE__));
    // LOG_INFO_PRINT(F("Using IRRemote version " VERSION_IRREMOTE));
#endif
    robot.begin();

    // Set the first state
    state.setState<InterruptStartRobotState>();
}

#if LOG_LEVEL >= LOG_DEBUG
uint16_t loopI = 0;
#endif

void loop() {
#if LOG_LEVEL >= LOG_DEBUG
    uint64_t sTime = millis();
    loopI++;
#endif

    // Update the hardware
    robot.update();
    // Update the state/strategy
    state.update();

#if LOG_LEVEL >= LOG_DEBUG
    uint64_t eTime = millis();
    // if ((loopI % 1000) == 0)
    // LOG_DEBUG_PRINTF("Loop took %llu ms", eTime - sTime);
#endif
}
