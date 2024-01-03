#include "lmq/engine/Robot/lmqRobotController.h"

#include "lmq/system/Logging/lmqLogging.h"

#include "lmq/engine/Robot/Controllers/lmqRobotAutoMovementController.h"
#include "lmq/engine/Robot/Controllers/lmqRobotHeadController.h"
#include "lmq/engine/Robot/Controllers/lmqRobotManualMovementController.h"
#include "lmq/engine/Robot/lmqRobot.h"

lmqRobotController::lmqRobotController(lmqRobot* robot)
    : m_autoMovementController(robot->GetAutoMovementController())
    , m_manualMovementController(robot->GetManualMovementController())
    , m_headController(robot->GetHeadController())
{
}

void lmqRobotController::Update()
{
}

void lmqRobotController::SetAutoMovementParams(
      const lmqAxis speedAxis
    , const lmqAxis turnAxis)
{
    if(!m_autoMovementController)
    {
        lmq_LOG_DEBUG("Can't use the auto move mode: controller is missing");
        return;
    }

    const int8_t speed = speedAxis.ToInt8();
    m_autoMovementController->SetSpeed(speed);
    if(speed != lmq_MOVEMENT_SPEED_STOP)
    {
        m_autoMovementController->SetTurn(turnAxis.ToInt8());
    }
}

void lmqRobotController::SetManualMovementParams(
      const lmqAxis leftChannelSpeedAxis
    , const lmqAxis rightChannelSpeedAxis)
{
    if(!m_manualMovementController)
    {
        lmq_LOG_DEBUG("Can't use the manual move mode: controller is missing");
        return;
    }

    m_manualMovementController->SetLChannelSpeed(
        leftChannelSpeedAxis.ToInt8());
    m_manualMovementController->SetRChannelSpeed(
        rightChannelSpeedAxis.ToInt8());
}

void lmqRobotController::RotateHead(const lmqAxis rotationAxis)
{
    if(!m_headController)
    {
        lmq_LOG_DEBUG("Can't rotate the head: controller is missing");
        return;
    }

    m_headController->Rotate(rotationAxis.ToInt8());
}