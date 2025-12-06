#include <Arduino.h>

#include "RobotState.h"
#include "StateMachine.h"
#include "hardware/DriveBase.h"
#include "hardware/LED.h"
#include "hardware/Motor.h"
#include "hardware/Pins.h"
#include "hardware/QRE.h"
#include "hardware/Sharp.h"

Motor leftMotor, rightMotor;
DriveBase drive;
LED ledRed, ledOrange;
QRE lineSensorLeft, lineSensorRight, lineSensorRear;
Sharp leftProximity, rightProximity;

StateMachine<RobotState> state(FORWARD);

void setup() {
    Serial.begin(115200);

    leftMotor = Motor(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL);
    rightMotor = Motor(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL);
    drive = DriveBase(leftMotor, rightMotor);

    ledRed = LED(PIN_LED_RED);
    ledOrange = LED(PIN_LED_ORANGE);

    lineSensorLeft = QRE(PIN_QRE_LEFT);
    lineSensorRight = QRE(PIN_QRE_RIGHT);
    lineSensorRear = QRE(PIN_QRE_REAR);

    leftProximity = Sharp(PIN_SHARP_LEFT);
    rightProximity = Sharp(PIN_SHARP_RIGHT);
}

void loop() {
    ledRed.update();
    ledOrange.update();
    state.update();

    const unsigned long stateDuration = state.getStateDuration();
    switch (state.getState()) {
        case FORWARD:
            drive.driveStraight(1.0f);
            if (lineSensorLeft.get() || lineSensorRight.get() || lineSensorRear.get()) {
                state.setState(BACKWARD);
            }
            break;

        case BACKWARD:
            drive.driveStraight(-1.0f);
            if (stateDuration > 500) state.setState(TURN);
            break;

        case TURN:
            drive.turnLeft(1.0f);
            if (stateDuration > 500) state.setState(FORWARD);
            break;
    }
}
