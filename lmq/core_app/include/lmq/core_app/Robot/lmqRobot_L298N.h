#pragma once

#include "lmq/engine/Robot/lmqRobot.h"

#include "lmq/engine/MotorDriver/lmqMotorDriver_L298N.h"
#include "lmq/engine/MovementController/lmqAutoMovementController_L298N.h"

class lmqRobot_L298N
    : public lmqRobot
{
public:
    lmqRobot_L298N(
          lmqMotorDriver_L298N::Channel mdChannelA
        , lmqMotorDriver_L298N::Channel mdChannelB);

    void Initialize();
    void SetMotorDriverPowerLimits(lmqPowerRange powerLimit);

    virtual lmqAutoMovementController* GetAutoMovementController() override;

private:
    lmqMotorDriver_L298N m_motorDriver;
    lmqAutoMovementController_L298N m_autoMovementController;
};