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

void loop() {
    // Update the hardware
    robot.update();
    // Update the state/strategy
    state.update();
}
