#include <Arduino.h>

#include "lmq/engine/InputController/lmqGamepadInputController.h"

#include "lmq/engine/InputController/lmqGamepadControlsState.h"
#include "lmq/engine/MovementController/lmqAutoMovementController.h"
#include "lmq/engine/MovementController/lmqManualMovementController.h"
#include "lmq/engine/Robot/lmqRobotController.h"

lmqGamepadInputController::lmqGamepadInputController(
    lmqRobotController* robotController)
    : m_robotController(robotController)
    , m_stickThreshold(0)
    , m_triggerThreshold(0)
    , m_movementMode(AUTO_MOVEMENT_MODE)
{
}

void lmqGamepadInputController::OnGamepadControlsState(
    lmqGamepadControlsState const& gamepadControlsState)
{
    if(gamepadControlsState.m_upPressed)
    {
        m_movementMode = m_movementMode == AUTO_MOVEMENT_MODE
            ? MANUAL_MOVEMENT_MODE
            : AUTO_MOVEMENT_MODE;
    }

    if(m_movementMode == AUTO_MOVEMENT_MODE)
    {
        if(m_robotController->GetAutoMovementController())
        {
            UpdateAutoMovementMode(gamepadControlsState);
        }
    }

    if(m_movementMode == MANUAL_MOVEMENT_MODE)
    {
        if(m_robotController->GetManualMovementController())
        {
            UpdateManualMovementMode(gamepadControlsState);
        }
    }
}

void lmqGamepadInputController::UpdateAutoMovementMode(
    const lmqGamepadControlsState& gamepadControlsState)
{
    const int8_t speed = gamepadControlsState.m_l2Value >= m_triggerThreshold
        ?   GetValueFromTrigger(
              gamepadControlsState.m_l2Value
            , 0, lmq_MOVEMENT_SPEED_BACKWARD)
        :   GetValueFromTrigger(
              gamepadControlsState.m_r2Value
            , 0, lmq_MOVEMENT_SPEED_FORWARD);
    
    auto autoMovementController = m_robotController->GetAutoMovementController();
    autoMovementController->SetSpeed(speed);
    
    if(speed != lmq_MOVEMENT_SPEED_STOP)
    {
        const int8_t turn= GetValueFromStick(
              gamepadControlsState.m_leftStickX
            , lmq_MOVEMENT_TURN_LEFT
            , lmq_MOVEMENT_TURN_RIGHT);
        autoMovementController->SetTurn(turn);
    }
}
    
void lmqGamepadInputController::UpdateManualMovementMode(
    const lmqGamepadControlsState& gamepadControlsState)
{
    const int8_t leftChSpeed = GetValueFromStick(
          gamepadControlsState.m_leftStickY
        , lmq_MOVEMENT_SPEED_BACKWARD
        , lmq_MOVEMENT_SPEED_FORWARD);

    const int8_t rightChSpeed = GetValueFromStick(
          gamepadControlsState.m_rightStickY
        , lmq_MOVEMENT_SPEED_BACKWARD
        , lmq_MOVEMENT_SPEED_FORWARD);

    auto manualMovementController
        = m_robotController->GetManualMovementController();
    manualMovementController->SetLChannelSpeed(leftChSpeed);
    manualMovementController->SetRChannelSpeed(rightChSpeed);
}

void lmqGamepadInputController::SetStickThreshold(const uint8_t stickThreshold)
{
    m_stickThreshold = stickThreshold;
}

void lmqGamepadInputController::SetTriggerThreshold(const uint8_t triggerThreshold)
{
    m_triggerThreshold = triggerThreshold;
}

int8_t lmqGamepadInputController::GetValueFromStick(
      const int8_t stickInput
    , const int8_t outMin
    , const int8_t outMax) const
{
    if(abs(stickInput) >= m_stickThreshold)
    {
        return stickInput >= 0
            ? map(stickInput, m_stickThreshold, 127, 0, outMax)
            : map(stickInput, -m_stickThreshold, -128, 0, outMin);
    }
    return 0;
}

int8_t lmqGamepadInputController::GetValueFromTrigger(
      const uint8_t triggerInput
    , const int8_t outMin
    , const int8_t outMax) const
{
    if(triggerInput >= m_triggerThreshold)
    {
        return map(triggerInput, m_triggerThreshold, 255
            , outMin, outMax);
    }
    return 0;
}