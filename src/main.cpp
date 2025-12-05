#include <Arduino.h>

#include "hardware/DriveBase.h"
#include "hardware/LED.h"
#include "hardware/Motor.h"
#include "hardware/Pins.h"

Motor motorLeft, motorRight;
DriveBase wheels;
LED redLED, orangeLED;
// TODO Line sensors
// TODO Side sensors

void setup() {
    Serial.begin(115200);

    motorLeft = Motor(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL);
    motorRight = Motor(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL);
    wheels = DriveBase(motorLeft, motorRight);
    redLED = LED(PIN_LED_RED);
    orangeLED = LED(PIN_LED_ORANGE);
}

void loop() {
    redLED.update();
    orangeLED.update();
}
