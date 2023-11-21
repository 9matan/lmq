#include "lmq/engine/MovementController/lmqManualMovementController_L298N.h"

#include <algorithm>
#include <math.h>

static void private_lmqManualMovementController_L298N_SetChannelSpeed(
      lmqMotorDriver_L298N* motorDriver
    , const lmqMotorDriver_L298N::EChannelFlag channelMask
    , const int8_t speed);

lmqManualMovementController_L298N::lmqManualMovementController_L298N(
      lmqMotorDriver_L298N* motorDriver
    , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask)
    : m_motorDriver(motorDriver)
    , m_leftChannelMask(leftChannelMask)
{
}

void lmqManualMovementController_L298N::SetLChannelSpeed(const int8_t speed)
{
    private_lmqManualMovementController_L298N_SetChannelSpeed(
          m_motorDriver
        , m_leftChannelMask
        , speed);
}

void lmqManualMovementController_L298N::SetRChannelSpeed(const int8_t speed)
{
    private_lmqManualMovementController_L298N_SetChannelSpeed(
          m_motorDriver
        , (lmqMotorDriver_L298N::EChannelFlag)( (~m_leftChannelMask)
            & lmqMotorDriver_L298N::EChannelFlag::ALL_CHANNELS)
        , speed);
}

static void private_lmqManualMovementController_L298N_SetChannelSpeed(
      lmqMotorDriver_L298N* motorDriver
    , const lmqMotorDriver_L298N::EChannelFlag channelMask
    , const int8_t speed)
{
    if(speed == lmq_MOVEMENT_SPEED_STOP)
    {
        motorDriver->SetMode(channelMask, lmqMotorDriver_L298N::EMode::STOP);
        motorDriver->SetPower(channelMask, lmq_MOVEMENT_SPEED_STOP);
        return;
    }

    motorDriver->SetMode(
          channelMask
        , speed >= 0
            ? lmqMotorDriver_L298N::EMode::FORWARD
            : lmqMotorDriver_L298N::EMode::BACKWARD);
    motorDriver->SetPower(
          channelMask
        , 2 * abs(std::max(speed, (int8_t)-127)));
}