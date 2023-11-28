#include "lmq/core_app/Robot/lmqRobot_L298N.h"

lmqRobot_L298N::lmqRobot_L298N(
      const lmqMotorDriver_L298N::Channel mdChannelA
    , const lmqMotorDriver_L298N::Channel mdChannelB
    , const lmqMotorDriver_L298N::EChannelFlag leftChannelMask
    , const uint8_t headServoMotorPin
    , const uint8_t headMaxAngleSpeed
    , const uint8_t headInitAngle)
    : m_motorDriver(mdChannelA, mdChannelB)
    , m_autoMovementController(&m_motorDriver, leftChannelMask)
    , m_manualMovementController(&m_motorDriver, leftChannelMask)
    , m_headServoMotor(headServoMotorPin)
    , m_headController(&m_headServoMotor, headInitAngle, headMaxAngleSpeed)
{
}

void lmqRobot_L298N::SetMotorDriverPowerLimits(
    lmqPowerRange powerLimit)
{
    m_motorDriver.SetPowerLimits(
        lmqMotorDriver_L298N::ALL_CHANNELS, powerLimit);
}

lmqRobotAutoMovementController* lmqRobot_L298N::GetAutoMovementController()
{
    return &m_autoMovementController;
}

lmqRobotManualMovementController* lmqRobot_L298N::GetManualMovementController()
{
    return &m_manualMovementController;
}

lmqRobotHeadController* lmqRobot_L298N::GetHeadController()
{
    return &m_headController;
}