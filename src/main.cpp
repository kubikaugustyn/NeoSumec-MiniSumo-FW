#include <Arduino.h>
#include "StateMachine.h"

auto robot = Robot();
auto state = StateMachine(robot);

void setup() {
    Serial.begin(115200);
    robot.begin();
}

void loop() {
    // Update the hardware
    robot.update();
    // Update the state/strategy
    state.update();
}
