//
// Created by Jakub Augustýn on 05.12.2025.
// Copyright (c) 2026 Jakub Augustýn. All rights reserved.
//
// Inspired by:
// https://github.com/NataniSi/Sumec-MiniSumo-SW/blob/main/main_sw/MAIN_CODE/include/Motion.h
//

#ifndef NEOSUMEC_SW_DRIVEBASE_H
#define NEOSUMEC_SW_DRIVEBASE_H
#include <Arduino.h>
#include <hardware/Motor.h>

/**
 * @brief A simple DriveBase class to move the robot forward/backward/left/right with the given velocity.
 */
class DriveBase {
private:
    Motor leftMotor, rightMotor;

    static inline float clamp(float value, float min, float max);
    static inline float clampNormalPositive(float value);
    static inline float clampNormal(float value);

public:
    DriveBase() = default;

    DriveBase(const Motor &leftMotor, const Motor &rightMotor);

    /**
    * @brief Moves the robot forward.
    * @param speed Desired speed of the robot (between -1.0 and 1.0).
    */
    void driveStraight(float speed) const;

    /**
    * @brief Turns the robot left in-place.
    * @param turningSpeed Desired turning speed of the robot (between 0.0 and 1.0).
    */
    void turnLeft(float turningSpeed) const;

    /**
    * @brief Turns the robot left in-place.
    * @param speed Desired speed of the robot (between -1.0 and 1.0).
    * @param turningSpeed Desired turning speed of the robot (between 0.0 and 1.0).
    */
    void turnLeft(float speed, float turningSpeed) const;

    /**
    * @brief Turns the robot right in-place.
    * @param turningSpeed Desired turning speed of the robot (between 0.0 and 1.0).
    */
    void turnRight(float turningSpeed) const;

    /**
    * @brief Turns the robot right in-place.
    * @param speed Desired speed of the robot (between -1.0 and 1.0).
    * @param turningSpeed Desired turning speed of the robot (between 0.0 and 1.0).
    */
    void turnRight(float speed, float turningSpeed) const;

    /**
    * @brief Turns the robot in-place. Uses arcade-style driving.
    * @param speed Desired speed of the robot (between -1.0 and 1.0).
    * @param turningSpeed Desired turning speed of the robot (between -1.0 and 1.0). Negative values mean turning right.
    */
    void turn(float speed, float turningSpeed) const;

    /**
    * @brief Turns the robot left in-place, spinning the wheels in opposite directions.
    * @param speed Desired speed of the robot (between 0.0 and 1.0).
    */
    void turnLeftTank(float speed) const;

    /**
    * @brief Turns the robot right in-place, spinning the wheels in opposite directions.
    * @param speed Desired speed of the robot (between 0.0 and 1.0).
    */
    void turnRightTank(float speed) const;

    /**
    * @brief Stops the robot.
    */
    void stop() const;
};
#endif //NEOSUMEC_SW_DRIVEBASE_H
