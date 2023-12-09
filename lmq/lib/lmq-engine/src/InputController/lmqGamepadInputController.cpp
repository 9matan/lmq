#include "lmq/engine/InputController/lmqGamepadInputController.h"

#include <math.h>

#include "lmq/core/lmqLerp.h"

#include "lmq/engine/InputController/lmqGamepadControlsState.h"
#include "lmq/engine/Robot/lmqRobotController.h"

lmqGamepadInputController::lmqGamepadInputController(
    lmqRobotController* robotController)
    : m_robotController(robotController)
    , m_stickThreshold(0)
    , m_triggerThreshold(0)
{
}

void lmqGamepadInputController::OnGamepadControlsState(
    lmqGamepadControlsState const& gamepadControlsState)
{
    if(gamepadControlsState.m_upPressed)
    {
        m_robotController->SwitchMovementMode();
    }

    const auto speed = gamepadControlsState.m_l2Value >= m_triggerThreshold
        ?   GetAxisFromTrigger(gamepadControlsState.m_l2Value).GetInverted()
        :   GetAxisFromTrigger(gamepadControlsState.m_r2Value);
    m_robotController->SetSpeed(speed);

    const auto turn = GetAxisFromStick(gamepadControlsState.m_leftStickX);
    m_robotController->SetTurn(turn);

    const auto lChannelSpeed = GetAxisFromStick(gamepadControlsState.m_leftStickY);
    m_robotController->SetLeftChannelSpeed(lChannelSpeed);

    const auto rChannelSpeed = GetAxisFromStick(gamepadControlsState.m_rightStickY);
    m_robotController->SetRightChannelSpeed(rChannelSpeed);

    const auto headRotationSpeed
        = GetAxisFromStick(gamepadControlsState.m_rightStickX).GetInverted();
    m_robotController->RotateHead(headRotationSpeed);
}

void lmqGamepadInputController::SetStickThreshold(const uint8_t stickThreshold)
{
    m_stickThreshold = stickThreshold;
}

void lmqGamepadInputController::SetTriggerThreshold(const uint8_t triggerThreshold)
{
    m_triggerThreshold = triggerThreshold;
}

lmqAxis lmqGamepadInputController::GetAxisFromStick(
      const int8_t stickInput) const
{
    if(stickInput == 0) return lmqAxis::Zero();
    if(abs(stickInput) >= m_stickThreshold / 2)
    {
        return lmqAxis::FromInt8(
            stickInput > 0
            ? lmqMapValue(stickInput, m_stickThreshold / 2, 127, 1, 127)
            : lmqMapValue(stickInput, -m_stickThreshold / 2, -128, -1, -128));
    }
    return lmqAxis::Zero();
}

lmqAxis lmqGamepadInputController::GetAxisFromTrigger(
    const uint8_t triggerInput) const
{
    if(triggerInput < m_triggerThreshold) return lmqAxis::Zero();
    
    return lmqAxis::FromInt8(
        lmqMapValue(triggerInput
            , m_triggerThreshold, 255
            , 1, 255) / 2);
}