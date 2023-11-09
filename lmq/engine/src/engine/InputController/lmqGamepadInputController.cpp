#include <Arduino.h>

#include "lmq/engine/InputController/lmqGamepadInputController.h"

#include "lmq/engine/InputController/lmqGamepadControlsState.h"
#include "lmq/engine/MovementController/lmqAutoMovementController.h"
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
    int8_t speed = lmq_MOVEMENT_SPEED_STOP;
    if(gamepadControlsState.m_r2Value >= m_triggerThreshold)
    {
        speed = map(gamepadControlsState.m_r2Value
                    , m_triggerThreshold, 255, 0, lmq_MOVEMENT_SPEED_FORWARD);
        
    }
    else if(gamepadControlsState.m_l2Value >= m_triggerThreshold)
    {
        speed = map(gamepadControlsState.m_l2Value
                    , m_triggerThreshold, 255, 0, lmq_MOVEMENT_SPEED_BACKWARD);
    }
    auto autoMovementController = m_robotController->GetAutoMovementController();
    autoMovementController->SetSpeed(speed);
    
    if(speed != lmq_MOVEMENT_SPEED_STOP)
    {
        int8_t turn = lmq_MOVEMENT_TURN_STRAIGHT;
        if(abs(gamepadControlsState.m_leftStickX) >= m_stickThreshold)
        {
            turn = gamepadControlsState.m_leftStickX >= 0
                 ? map(gamepadControlsState.m_leftStickX
                        , m_stickThreshold, 127, 0, lmq_MOVEMENT_TURN_RIGHT)
                 : map(gamepadControlsState.m_leftStickX
                        , -m_stickThreshold, -127, 0, lmq_MOVEMENT_TURN_LEFT);
        }
        autoMovementController->SetTurn(turn);
    }
}

void lmqGamepadInputController::SetStickThreshold(const uint8_t stickThreshold)
{
    m_stickThreshold = stickThreshold;
}

void lmqGamepadInputController::SetTriggerThreshold(const uint8_t triggerThreshold)
{
    m_triggerThreshold = triggerThreshold;
}