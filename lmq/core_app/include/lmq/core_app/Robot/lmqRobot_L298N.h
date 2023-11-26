#pragma once

#include "lmq/engine/Robot/lmqRobot.h"

#include "lmq/core_app/Components/lmqMotorDriver_L298N.h"
#include "lmq/core_app/Robot/Controllers/lmqRobotAutoMovementController_L298N.h"
#include "lmq/core_app/Robot/Controllers/lmqRobotManualMovementController_L298N.h"

class lmqRobot_L298N
    : public lmqRobot
{
public:
    lmqRobot_L298N(
          const lmqMotorDriver_L298N::Channel mdChannelA
        , const lmqMotorDriver_L298N::Channel mdChannelB
        , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask);

    void Initialize();
    void SetMotorDriverPowerLimits(lmqPowerRange powerLimit);

    virtual lmqRobotAutoMovementController* GetAutoMovementController() override;
    virtual lmqRobotManualMovementController* GetManualMovementController() override;

private:
    lmqMotorDriver_L298N m_motorDriver;
    lmqRobotAutoMovementController_L298N m_autoMovementController;
    lmqRobotManualMovementController_L298N m_manualMovementController;
};