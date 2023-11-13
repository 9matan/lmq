#include "lmq/core_app/Robot/lmqRobot_L298N.h"

lmqRobot_L298N::lmqRobot_L298N(
      const lmqMotorDriver_L298N::Channel mdChannelA
    , const lmqMotorDriver_L298N::Channel mdChannelB
    , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask)
    : m_motorDriver(mdChannelA, mdChannelB)
    , m_autoMovementController(&m_motorDriver, leftChannelMask)
    , m_manualMovementController(&m_motorDriver, leftChannelMask)
{
}

void lmqRobot_L298N::Initialize()
{
    m_motorDriver.Initialize();
}

void lmqRobot_L298N::SetMotorDriverPowerLimits(
    lmqPowerRange powerLimit)
{
    m_motorDriver.SetPowerLimits(
        lmqMotorDriver_L298N::ALL_CHANNELS, powerLimit);
}

lmqAutoMovementController* lmqRobot_L298N::GetAutoMovementController()
{
    return &m_autoMovementController;
}

lmqManualMovementController* lmqRobot_L298N::GetManualMovementController()
{
    return &m_manualMovementController;
}