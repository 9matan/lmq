#include <Arduino.h>

#include "lmq/engine/MovementController/lmqAutoMovementController_L298N.h"

#include "lmq/engine/MotorDriver/lmqMotorDriver_L298N.h"

#ifdef lmq_MOTOR_DRIVER_L298N_LEFT_CHANNEL
#define lmqAutoMovementController_L298N_LeftChannel (lmqMotorDriver_L298N::EChannelFlag)lmq_MOTOR_DRIVER_L298N_LEFT_CHANNEL
#else
#define lmqAutoMovementController_L298N_LeftChannel lmqMotorDriver_L298N::CHANNELA
#endif

#ifdef lmq_MOTOR_DRIVER_L298N_RIGHT_CHANNEL
#define lmqAutoMovementController_L298N_RightChannel (lmqMotorDriver_L298N::EChannelFlag)lmq_MOTOR_DRIVER_L298N_RIGHT_CHANNEL
#else
#define lmqAutoMovementController_L298N_RightChannel lmqMotorDriver_L298N::CHANNELB
#endif

lmqAutoMovementController_L298N::lmqAutoMovementController_L298N(
      lmqMotorDriver_L298N* motorDriver)
    : m_motorDriver(motorDriver)
    , m_speed(0)
    , m_turn(0)
{
}

void lmqAutoMovementController_L298N::SetSpeed(int8_t speed)
{
    m_speed = speed;
    UpdateEnginePower();
}

void lmqAutoMovementController_L298N::SetTurn(int8_t turn)
{
    // -128 is not used
    m_turn = max(turn, (int8_t)lmq_MOVEMENT_TURN_LEFT);
    UpdateEnginePower();
}

void lmqAutoMovementController_L298N::UpdateEnginePower()
{
    if(m_speed == lmq_MOVEMENT_SPEED_STOP)
    {
        m_motorDriver->SetPower(lmqMotorDriver_L298N::ALL_CHANNELS, 0);
        m_motorDriver->SetMode(lmqMotorDriver_L298N::ALL_CHANNELS, lmqMotorDriver_L298N::STOP);
        return;
    }

    const int8_t leftChannelSpeed = map( min((int8_t)0, m_turn), lmq_MOVEMENT_TURN_LEFT, 0, -m_speed, m_speed);
    const int8_t rightChannelSpeed = map( max((int8_t)0, m_turn), lmq_MOVEMENT_TURN_RIGHT, 0, -m_speed, m_speed);
    
    m_motorDriver->SetPower(
          lmqAutoMovementController_L298N_LeftChannel
        , 2 * abs(leftChannelSpeed));
    m_motorDriver->SetPower(
          lmqAutoMovementController_L298N_RightChannel
        , 2 * abs(rightChannelSpeed));

    m_motorDriver->SetMode(
          lmqAutoMovementController_L298N_LeftChannel
        , leftChannelSpeed >= 0 ? lmqMotorDriver_L298N::FORWARD : lmqMotorDriver_L298N::BACKWARD);
    m_motorDriver->SetMode(
          lmqAutoMovementController_L298N_RightChannel
        , rightChannelSpeed >= 0 ? lmqMotorDriver_L298N::FORWARD : lmqMotorDriver_L298N::BACKWARD);
}