#include <Arduino.h>

#include "lmq/core_app/Robot/Controllers/lmqRobotManualMovementController_L298N.h"

static void private_lmqRobotManualMovementController_L298N_SetChannelSpeed(
      lmqMotorDriver_L298N* motorDriver
    , const lmqMotorDriver_L298N::EChannelFlag channelMask
    , const int8_t speed);

lmqRobotManualMovementController_L298N::lmqRobotManualMovementController_L298N(
      lmqMotorDriver_L298N* motorDriver
    , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask)
    : m_motorDriver(motorDriver)
    , m_leftChannelMask(leftChannelMask)
{
}

void lmqRobotManualMovementController_L298N::SetLChannelSpeed(const int8_t speed)
{
    private_lmqRobotManualMovementController_L298N_SetChannelSpeed(
          m_motorDriver
        , m_leftChannelMask
        , speed);
}

void lmqRobotManualMovementController_L298N::SetRChannelSpeed(const int8_t speed)
{
    private_lmqRobotManualMovementController_L298N_SetChannelSpeed(
          m_motorDriver
        , (lmqMotorDriver_L298N::EChannelFlag)( (~m_leftChannelMask)
            & lmqMotorDriver_L298N::EChannelFlag::ALL_CHANNELS)
        , speed);
}

static void private_lmqRobotManualMovementController_L298N_SetChannelSpeed(
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
        , 2 * abs(max(speed, (int8_t)-127)));
}