#include "lmq/app/Robot/lmqRobotPS4InputController.h"

#include "lmq/core/lmqLerp.h"

#include "lmq/system/Input/Controller/lmqPS4ControllerKeyCodes.h"
#include "lmq/system/Input/lmqInputSystem.h"
#include "lmq/system/Logging/lmqLogging.h"

#include "lmq/engine/Robot/lmqRobotController.h"

lmqRobotPS4InputController::lmqRobotPS4InputController(
      lmqInputSystem* inputSystem
    , lmqRobotController* robotController)
    : m_inputSystem(inputSystem)
    , m_robotController(robotController)
    , m_layout(LAYOUT_AUTO_MOVE)
{
}

void lmqRobotPS4InputController::Update()
{
    if(m_inputSystem->IsKeyPressed(lmqPS4KeyCode::Up))
    {
        lmq_LOG_INFO("Switching PS4 layout");
        SwitchLayout();
    }

    UpdateCurrentLayout();
}

void lmqRobotPS4InputController::SwitchLayout()
{
    if(m_layout == LAYOUT_AUTO_MOVE) m_layout = LAYOUT_MANUAL_MOVE;
    else m_layout = LAYOUT_AUTO_MOVE;
}

void lmqRobotPS4InputController::UpdateCurrentLayout()
{
    if(m_layout == LAYOUT_AUTO_MOVE)
    {
        UpdateAutoMoveLayout();
    }
    else
    {
        UpdateManualMoveLayout();
    }
}

void lmqRobotPS4InputController::UpdateAutoMoveLayout()
{
    const auto speed = m_inputSystem->GetAxis(lmqPS4AxisCode::R2)
                        + m_inputSystem->GetAxis(lmqPS4AxisCode::L2).GetInverted();
    const auto turn = m_inputSystem->GetAxis(lmqPS4AxisCode::LeftStickX);
    m_robotController->SetAutoMovementParams(speed, turn);

    UpdateHead();
}

void lmqRobotPS4InputController::UpdateManualMoveLayout()
{
    const auto lChannelSpeed = m_inputSystem->GetAxis(lmqPS4AxisCode::LeftStickY);
    const auto rChannelSpeed = m_inputSystem->GetAxis(lmqPS4AxisCode::RightStickY);
    m_robotController->SetManualMovementParams(lChannelSpeed, rChannelSpeed);

    UpdateHead();
}

void lmqRobotPS4InputController::UpdateHead()
{
    const auto headRotationSpeed
        = m_inputSystem->GetAxis(lmqPS4AxisCode::RightStickX).GetInverted();
    m_robotController->RotateHead(headRotationSpeed);
}