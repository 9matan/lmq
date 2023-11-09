#include <string.h>

#include <Arduino.h>

#include "lmq/engine/InputController/lmqConsoleInputController.h"

#include "lmq/system/Console/lmqConsole.h"
#include "lmq/system/Console/lmqConsoleListener.h"

#include "lmq/engine/MovementController/lmqAutoMovementController.h"
#include "lmq/engine/Robot/lmqRobotController.h"


#define lmq_CMP_STR_ARR(strArr, str) strncmp(strArr, str, sizeof(strArr)-1)

lmqConsoleInputController::lmqConsoleInputController(
      const lmqRobotController* robotController)
    : m_robotController(robotController)
{
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
    if(lmq_CMP_STR_ARR(cmdStop, line) == 0)
    {
        autoMovementController->SetSpeed(lmq_MOVEMENT_SPEED_STOP);
    }
    else if(lmq_CMP_STR_ARR(cmdMoveForward, line) == 0)
    {
        autoMovementController->SetSpeed(lmq_MOVEMENT_SPEED_FORWARD);
    }
    else if(lmq_CMP_STR_ARR(cmdMoveBackward, line) == 0)
    {
        autoMovementController->SetSpeed(lmq_MOVEMENT_SPEED_BACKWARD);
    }
    else if(lmq_CMP_STR_ARR(cmdTurnStraight, line) == 0)
    {
        autoMovementController->SetTurn(lmq_MOVEMENT_TURN_STRAIGHT);
    }
    else if(lmq_CMP_STR_ARR(cmdTurnLeft, line) == 0)
    {
        autoMovementController->SetTurn(lmq_MOVEMENT_TURN_LEFT);
    }
    else if(lmq_CMP_STR_ARR(cmdTurnRight, line) == 0)
    {
        autoMovementController->SetTurn(lmq_MOVEMENT_TURN_RIGHT);
    }
}