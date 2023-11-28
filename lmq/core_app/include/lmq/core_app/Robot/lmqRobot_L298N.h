#pragma once

#include "lmq/engine/Robot/lmqRobot.h"

#include "lmq/core_app/Components/lmqMotorDriver_L298N.h"
#include "lmq/core_app/Components/ServoMotor/lmqServoMotor_SG90_CFsunbird.h"
#include "lmq/core_app/Robot/Controllers/lmqRobotAutoMovementController_L298N.h"
#include "lmq/core_app/Robot/Controllers/lmqRobotHeadController_Servo.h"
#include "lmq/core_app/Robot/Controllers/lmqRobotManualMovementController_L298N.h"

class lmqRobot_L298N
    : public lmqRobot
{
public:
    lmqRobot_L298N(
          const lmqMotorDriver_L298N::Channel mdChannelA
        , const lmqMotorDriver_L298N::Channel mdChannelB
        , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask
        , const uint8_t headServoMotorPin
        , const uint8_t headMaxAngleSpeed
        , const uint8_t headInitAngle);

    void SetMotorDriverPowerLimits(lmqPowerRange powerLimit);

    virtual lmqRobotAutoMovementController* GetAutoMovementController() override;
    virtual lmqRobotManualMovementController* GetManualMovementController() override;
    virtual lmqRobotHeadController* GetHeadController() override;

private:
    lmqMotorDriver_L298N m_motorDriver;
    lmqRobotAutoMovementController_L298N m_autoMovementController;
    lmqRobotManualMovementController_L298N m_manualMovementController;

    lmqServoMotor_SG90_CFsunbird m_headServoMotor;
    lmqRobotHeadController_Servo m_headController;
};