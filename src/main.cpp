//
// Created by Jakub Augustýn at 05.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//

#include <Arduino.h>
#include "StateMachine.h"
#include "RobotState.h"

auto robot = Robot();
auto state = StateMachine(robot);

void setup() {
    Serial.begin(115200);
    robot.begin();

    // Set the first state
    state.setState<DriveForwardState>();

    // Temporary: blink the LEDs to confirm the uploads actually work
    robot.ledRed.blink(500);
    robot.ledOrange.blink(1000);
}

void debugLoop();

void loop() {
    // Update the hardware
    robot.update();
    // Update the state/strategy
    state.update();

    // debugLoop();
}

void debugLoop() {
    Serial.printf("Rear %d Left %d Right %d\n", robot.lineSensorRear.get(), robot.lineSensorLeft.get(),
                  robot.lineSensorRight.get());
    delay(500);
}
