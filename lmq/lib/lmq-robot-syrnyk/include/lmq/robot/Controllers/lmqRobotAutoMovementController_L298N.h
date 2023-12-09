#pragma once

#include <stdint.h>

#include "lmq/engine/Robot/Controllers/lmqRobotAutoMovementController.h"
#include "lmq/component/MotorDriver/lmqMotorDriver_L298N.h"

class lmqMotorDriver_L298N;

class lmqRobotAutoMovementController_L298N
    : public lmqRobotAutoMovementController
{
public:
    lmqRobotAutoMovementController_L298N(
          lmqMotorDriver_L298N* motorDriver
        , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask);

    virtual void SetSpeed(int8_t speed) override;
    virtual void SetTurn(int8_t turn) override;

private:
    lmqMotorDriver_L298N* m_motorDriver;
    lmqMotorDriver_L298N::EChannelFlag m_leftChannelMask;
    int8_t m_speed;
    int8_t m_turn;

private:
    void UpdateEnginePower();
    void UpdateChannelSpeed(
          const lmqMotorDriver_L298N::EChannelFlag channelMask
        , const int8_t speed);
};