#pragma once

#include "lmq/engine/Robot/lmqRobot.h"

#include "lmq/component/MotorDriver/lmqMotorDriver_L298N.h"
#include "lmq/component/ServoMotor/lmqServoMotor_SG90_CFsunbird.h"
#include "lmq/robot/Controllers/lmqRobotAutoMovementController_L298N.h"
#include "lmq/robot/Controllers/lmqRobotHeadController_Servo.h"
#include "lmq/robot/Controllers/lmqRobotManualMovementController_L298N.h"

class lmqRobot_Syrnyk
    : public lmqRobot
{
public:
    lmqRobot_Syrnyk(
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