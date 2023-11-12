#pragma once

#include "lmq/engine/MotorDriver/lmqMotorDriver_L298N.h"
#include "lmq/engine/MovementController/lmqManualMovementController.h"

class lmqManualMovementController_L298N
    : public lmqManualMovementController
{
public:
    lmqManualMovementController_L298N(
          lmqMotorDriver_L298N* motorDriver
        , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask);

    virtual void SetLChannelSpeed(const int8_t speed) override;
    virtual void SetRChannelSpeed(const int8_t speed) override;

private:
    lmqMotorDriver_L298N* m_motorDriver;
    lmqMotorDriver_L298N::EChannelFlag m_leftChannelMask;
};