#include <limits.h>
#include <string.h>

#include <Arduino.h>

#include "lmq/engine/InputController/lmqConsoleInputController.h"

#include "lmq/system/Console/lmqConsole.h"
#include "lmq/system/Console/lmqConsoleListener.h"

#include "lmq/engine/MovementController/lmqAutoMovementController.h"
#include "lmq/engine/Robot/lmqRobotController.h"

#define lmqConsoleInputController_TIME_TO_RESET_SPEAD 500
#define lmqConsoleInputController_CMP_STR_ARR(strArr, str) strncmp(strArr, str, sizeof(strArr)-1)

lmqConsoleInputController::lmqConsoleInputController(
      const lmqRobotController* robotController)
    : m_robotController(robotController)
    , m_timePointToResetSpeed(ULONG_MAX)
{
}

void lmqConsoleInputController::Update()
{
    if(m_timePointToResetSpeed < millis())
    {
        m_robotController->GetAutoMovementController()
            ->SetSpeed(lmq_MOVEMENT_SPEED_STOP);
    }
}

void lmqConsoleInputController::OnConsoleInput(
    const char* line)
{
    const char cmdTurnLeft[] = "turn-l";
    const char cmdTurnRight[] = "turn-r";
    const char cmdTurnStraight[] = "turn-s";
    const char cmdMoveForward[] = "move-f";
    const char cmdMoveBackward[] = "move-b";
    const char cmdStop[] = "stop";

    auto autoMovementController = m_robotController->GetAutoMovementController();
    bool runResetSpeedTimer = false;
    if(lmqConsoleInputController_CMP_STR_ARR(cmdStop, line) == 0)
    {
        autoMovementController->SetSpeed(lmq_MOVEMENT_SPEED_STOP);
    }
    else if(lmqConsoleInputController_CMP_STR_ARR(cmdMoveForward, line) == 0)
    {
        runResetSpeedTimer = true;
        autoMovementController->SetSpeed(lmq_MOVEMENT_SPEED_FORWARD);
    }
    else if(lmqConsoleInputController_CMP_STR_ARR(cmdMoveBackward, line) == 0)
    {
        runResetSpeedTimer = true;
        autoMovementController->SetSpeed(lmq_MOVEMENT_SPEED_BACKWARD);
    }
    else if(lmqConsoleInputController_CMP_STR_ARR(cmdTurnStraight, line) == 0)
    {
        autoMovementController->SetTurn(lmq_MOVEMENT_TURN_STRAIGHT);
    }
    else if(lmqConsoleInputController_CMP_STR_ARR(cmdTurnLeft, line) == 0)
    {
        autoMovementController->SetTurn(lmq_MOVEMENT_TURN_LEFT);
    }
    else if(lmqConsoleInputController_CMP_STR_ARR(cmdTurnRight, line) == 0)
    {
        autoMovementController->SetTurn(lmq_MOVEMENT_TURN_RIGHT);
    }

    if(runResetSpeedTimer)
    {
        m_timePointToResetSpeed
            = millis() + lmqConsoleInputController_TIME_TO_RESET_SPEAD;
    }
}