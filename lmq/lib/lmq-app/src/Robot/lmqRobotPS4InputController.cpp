#include "lmq/app/Robot/lmqRobotPS4InputController.h"

#include "lmq/core/lmqLerp.h"

#include "lmq/system/Input/Controller/lmqPS4ControllerKeyCodes.h"
#include "lmq/system/Input/lmqInputSystem.h"

#include "lmq/engine/Robot/lmqRobotController.h"

lmqRobotPS4InputController::lmqRobotPS4InputController(
      lmqInputSystem* inputSystem
    , lmqRobotController* robotController)
    : m_inputSystem(inputSystem)
    , m_robotController(robotController)
{
}

void lmqRobotPS4InputController::Update()
{
    if(m_inputSystem->IsKeyPressed(lmqPS4KeyCode::Up))
    {
        m_robotController->SwitchMovementMode();
    }

    const auto l2Val = m_inputSystem->GetAxis(lmqPS4AxisCode::L2).GetInverted();
    const auto r2Val = m_inputSystem->GetAxis(lmqPS4AxisCode::R2);
    m_robotController->SetSpeed(l2Val + r2Val);
    m_robotController->SetTurn(m_inputSystem->GetAxis(lmqPS4AxisCode::LeftStickX));

    m_robotController->SetLeftChannelSpeed(
        m_inputSystem->GetAxis(lmqPS4AxisCode::LeftStickY));
    m_robotController->SetRightChannelSpeed(
        m_inputSystem->GetAxis(lmqPS4AxisCode::RightStickY));

    const auto headRotationSpeed
        = m_inputSystem->GetAxis(lmqPS4AxisCode::RightStickX).GetInverted();
    m_robotController->RotateHead(headRotationSpeed);
}