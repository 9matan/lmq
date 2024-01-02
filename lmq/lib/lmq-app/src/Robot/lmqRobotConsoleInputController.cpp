#include "lmq/app/Robot/lmqRobotConsoleInputController.h"

#include <limits.h>
#include <string.h>

#ifdef ARDUINO
#include <Arduino.h>
#endif // ARDUINO

#include "lmq/system/Console/lmqConsole.h"
#include "lmq/system/Console/lmqConsoleListener.h"

#include "lmq/engine/Robot/lmqRobotController.h"

#define lmqRobotConsoleInputController_TIME_TO_RESET_SPEED 500
#define lmqRobotConsoleInputController_CMP_STR_ARR(strArr, str) strncmp(strArr, str, sizeof(strArr)-1)

lmqRobotConsoleInputController::lmqRobotConsoleInputController(
      lmqRobotController* robotController)
    : m_robotController(robotController)
    , m_timePointToResetSpeed(ULONG_MAX)
{
}

void lmqRobotConsoleInputController::Update()
{
#ifdef ARDUINO
    if(m_timePointToResetSpeed < millis())
    {
        m_robotController->SetSpeed(lmqAxis::Zero());
    }
#endif // ARDUINO
}

void lmqRobotConsoleInputController::OnConsoleInput(
    const char* line)
{
    const char cmdTurnLeft[] = "turn-l";
    const char cmdTurnRight[] = "turn-r";
    const char cmdTurnStraight[] = "turn-s";
    const char cmdMoveForward[] = "move-f";
    const char cmdMoveBackward[] = "move-b";
    const char cmdStop[] = "stop";

    Serial.print(line);
    bool runResetSpeedTimer = false;
    if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdStop, line) == 0)
    {
        m_robotController->SetSpeed(lmqAxis::Zero());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveForward, line) == 0)
    {
        runResetSpeedTimer = true;
        m_robotController->SetSpeed(lmqAxis::Max());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveBackward, line) == 0)
    {
        runResetSpeedTimer = true;
        m_robotController->SetSpeed(lmqAxis::Min());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdTurnStraight, line) == 0)
    {
        m_robotController->SetTurn(lmqAxis::Zero());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdTurnLeft, line) == 0)
    {
        m_robotController->SetTurn(lmqAxis::Min());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdTurnRight, line) == 0)
    {
        m_robotController->SetTurn(lmqAxis::Max());
    }

    if(runResetSpeedTimer)
    {
#ifdef ARDUINO
        m_timePointToResetSpeed
            = millis() + lmqRobotConsoleInputController_TIME_TO_RESET_SPEED;
#endif // ARDUINO
    }
}