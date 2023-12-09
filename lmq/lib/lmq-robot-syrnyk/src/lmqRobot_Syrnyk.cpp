#include "lmq/robot/lmqRobot_Syrnyk.h"

lmqRobot_Syrnyk::lmqRobot_Syrnyk(
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

void lmqRobot_Syrnyk::SetMotorDriverPowerLimits(
    lmqPowerRange powerLimit)
{
    m_motorDriver.SetPowerLimits(
        lmqMotorDriver_L298N::ALL_CHANNELS, powerLimit);
}

lmqRobotAutoMovementController* lmqRobot_Syrnyk::GetAutoMovementController()
{
    return &m_autoMovementController;
}

lmqRobotManualMovementController* lmqRobot_Syrnyk::GetManualMovementController()
{
    return &m_manualMovementController;
}

lmqRobotHeadController* lmqRobot_Syrnyk::GetHeadController()
{
    return &m_headController;
}