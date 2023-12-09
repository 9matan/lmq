#pragma once

#include "lmq/engine/Robot/Controllers/lmqRobotHeadController.h"

class lmqServoMotor;

class lmqRobotHeadController_Servo
    : public lmqRobotHeadController
{
public:
    lmqRobotHeadController_Servo(
          lmqServoMotor* servoMotor
        , const uint8_t initAngle
        , const uint8_t maxAngleSpeed);

    virtual void Rotate(const int8_t speed) override;

private:
    uint8_t m_maxAngleSpeed;
    uint8_t m_currentAngle;
    lmqServoMotor* m_servo;
};