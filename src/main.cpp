//
// Created by Jakub Augustýn at 05.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <Arduino.h>

#include "MainConfig.h"
#include "StateMachine.h"

auto robot = Robot();
auto state = StateMachine(robot);

void setup() {
    Serial.begin(115200);
    robot.begin();

    // Set the first state
    state.setState<STRATEGY_INITIAL_STATE>();

    // Temporary: blink the LEDs to confirm the uploads actually work
    robot.ledRed.blink(500);
    robot.ledOrange.blink(1000);
}

void loop() {
    // Update the hardware
    robot.update();
    // Update the state/strategy
    state.update();
}