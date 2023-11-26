#pragma once

#include "lmq/engine/Robot/Controllers/lmqRobotManualMovementController.h"
#include "lmq/core_app/Components/lmqMotorDriver_L298N.h"

class lmqRobotManualMovementController_L298N
    : public lmqRobotManualMovementController
{
public:
    lmqRobotManualMovementController_L298N(
          lmqMotorDriver_L298N* motorDriver
        , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask);

    virtual void SetLChannelSpeed(const int8_t speed) override;
    virtual void SetRChannelSpeed(const int8_t speed) override;

private:
    lmqMotorDriver_L298N* m_motorDriver;
    lmqMotorDriver_L298N::EChannelFlag m_leftChannelMask;
};