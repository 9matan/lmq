#include "lmq/engine/Robot/lmqRobotController.h"

#include "lmq/system/Logging/lmqLogging.h"

#include "lmq/engine/MovementController/lmqAutoMovementController.h"
#include "lmq/engine/MovementController/lmqManualMovementController.h"
#include "lmq/engine/Robot/lmqRobot.h"

lmqRobotController::lmqRobotController(lmqRobot* robot)
    : m_autoMovementController(robot->GetAutoMovementController())
    , m_manualMovementController(robot->GetManualMovementController())
    , m_movementMode(MOVEMENT_MODE_NONE)
    , m_speedAxis(lmqAxis::Zero())
    , m_turnAxis(lmqAxis::Zero())
{
    if(m_autoMovementController) m_movementMode = MOVEMENT_MODE_AUTO;
    else if(m_manualMovementController) m_movementMode = MOVEMENT_MODE_MANUAL;
}

void lmqRobotController::Update()
{
    if(m_movementMode == MOVEMENT_MODE_AUTO)
    {
        UpdateAutoMovementMode();
    }
    else if(m_movementMode == MOVEMENT_MODE_MANUAL)
    {
        UpdateManualMovementMode();
    }
}

void lmqRobotController::UpdateAutoMovementMode()
{
    const int8_t speed = m_speedAxis.ToInt8();
    m_autoMovementController->SetSpeed(speed);
    if(speed != lmq_MOVEMENT_SPEED_STOP)
    {
        m_autoMovementController->SetTurn(m_turnAxis.ToInt8());
    }
}

void lmqRobotController::UpdateManualMovementMode()
{
    m_manualMovementController->SetLChannelSpeed(
        m_leftChannelSpeedAxis.ToInt8());
    m_manualMovementController->SetRChannelSpeed(
        m_rightChannelSpeedAxis.ToInt8());
}

void lmqRobotController::SwitchMovementMode()
{
    if(m_movementMode == MOVEMENT_MODE_AUTO)
    {
        if(m_manualMovementController)
        {
            lmq_LOG_INFO("Switch the move mode to manual");
            m_movementMode = MOVEMENT_MODE_MANUAL;
        }
        else
        {
            lmq_LOG_DEBUG("Can't set the manual move mode: controller is missing");
        }
    }
    else if(m_movementMode == MOVEMENT_MODE_MANUAL)
    {
        if(m_autoMovementController)
        {
            lmq_LOG_INFO("Switch the move mode to auto");
            m_movementMode = MOVEMENT_MODE_AUTO;
        }
        else
        {
            lmq_LOG_DEBUG("Can't set the auto move mode: controller is missing");
        }
    }
    else
    {
        lmq_LOG_ERROR("Cat't set the move mode: there are no controllers");
    }
}

void lmqRobotController::SetTurn(const lmqAxis axis)
{
    if(m_movementMode == MOVEMENT_MODE_AUTO)
    {
        m_turnAxis = axis;
    }
}

void lmqRobotController::SetSpeed(const lmqAxis axis)
{
    if(m_movementMode == MOVEMENT_MODE_AUTO)
    {
        m_speedAxis = axis;
    }
}

void lmqRobotController::SetLeftChannelSpeed(const lmqAxis axis)
{
    if(m_movementMode == MOVEMENT_MODE_MANUAL)
    {
        m_leftChannelSpeedAxis = axis;
    }
}

void lmqRobotController::SetRightChannelSpeed(const lmqAxis axis)
{
    if(m_movementMode == MOVEMENT_MODE_MANUAL)
    {
        m_rightChannelSpeedAxis = axis;
    }
}