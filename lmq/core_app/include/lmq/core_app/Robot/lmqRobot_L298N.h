#pragma once

#include "lmq/engine/Robot/lmqRobot.h"

#include "lmq/engine/MotorDriver/lmqMotorDriver_L298N.h"
#include "lmq/engine/MovementController/lmqAutoMovementController_L298N.h"
#include "lmq/engine/MovementController/lmqManualMovementController_L298N.h"

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

    virtual lmqAutoMovementController* GetAutoMovementController() override;
    virtual lmqManualMovementController* GetManualMovementController() override;

private:
    lmqMotorDriver_L298N m_motorDriver;
    lmqAutoMovementController_L298N m_autoMovementController;
    lmqManualMovementController_L298N m_manualMovementController;
};