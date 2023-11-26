#include <Arduino.h>

#include "lmq/core_app/Robot/Controllers/lmqRobotAutoMovementController_L298N.h"

lmqRobotAutoMovementController_L298N::lmqRobotAutoMovementController_L298N(
      lmqMotorDriver_L298N* motorDriver
    , lmqMotorDriver_L298N::EChannelFlag leftChannelMask)
    : m_motorDriver(motorDriver)
    , m_leftChannelMask(leftChannelMask)
    , m_speed(0)
    , m_turn(0)
{
}

void lmqRobotAutoMovementController_L298N::SetSpeed(int8_t speed)
{
    // -128 is not used
    m_speed = max(speed, (int8_t)-127);
    UpdateEnginePower();
}

void lmqRobotAutoMovementController_L298N::SetTurn(int8_t turn)
{
    // -128 is not used
    m_turn = max(turn, (int8_t)-127);
    UpdateEnginePower();
}

void lmqRobotAutoMovementController_L298N::UpdateEnginePower()
{
    if(m_speed == lmq_MOVEMENT_SPEED_STOP)
    {
        m_motorDriver->SetPower(lmqMotorDriver_L298N::ALL_CHANNELS, 0);
        m_motorDriver->SetMode(lmqMotorDriver_L298N::ALL_CHANNELS, lmqMotorDriver_L298N::STOP);
        return;
    }

    const int8_t leftChannelSpeed = map(
        min((int8_t)0, m_turn), lmq_MOVEMENT_TURN_LEFT, 0, -m_speed, m_speed);
    const int8_t rightChannelSpeed = map(
        max((int8_t)0, m_turn), lmq_MOVEMENT_TURN_RIGHT, 0, -m_speed, m_speed);

    UpdateChannelSpeed(m_leftChannelMask, leftChannelSpeed);
    const auto rightChannelMask = (lmqMotorDriver_L298N::EChannelFlag)
            ((~m_leftChannelMask)
             & lmqMotorDriver_L298N::EChannelFlag::ALL_CHANNELS);
    UpdateChannelSpeed(rightChannelMask, rightChannelSpeed);
}

void lmqRobotAutoMovementController_L298N::UpdateChannelSpeed(
      const lmqMotorDriver_L298N::EChannelFlag channelMask
    , const int8_t speed)
{
    m_motorDriver->SetPower(channelMask, 2 * abs(speed));
    m_motorDriver->SetMode(
          channelMask
        , speed >= 0 ? lmqMotorDriver_L298N::FORWARD : lmqMotorDriver_L298N::BACKWARD);   
}