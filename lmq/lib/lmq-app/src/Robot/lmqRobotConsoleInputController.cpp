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
    if(m_timePointToResetSpeed != ULONG_MAX && m_timePointToResetSpeed < millis())
    {
        m_timePointToResetSpeed = ULONG_MAX;
        m_robotController->SetAutoMovementParams(
              lmqAxis::Zero()
            , lmqAxis::Zero());
    }
#endif // ARDUINO
}

void lmqRobotConsoleInputController::OnConsoleInput(
    const char* line)
{
    const char cmdStop[] = "stop";
    const char cmdMoveFL[] = "move-fl";
    const char cmdMoveFR[] = "move-fr";
    const char cmdMoveF[] = "move-f";
    const char cmdMoveBL[] = "move-bl";
    const char cmdMoveBR[] = "move-br";
    const char cmdMoveB[] = "move-b";

    bool runResetSpeedTimer = true;
    if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdStop, line) == 0)
    {
        runResetSpeedTimer = false;
        m_robotController->SetAutoMovementParams(
              lmqAxis::Zero()
            , lmqAxis::Zero());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveFL, line) == 0)
    {
        m_robotController->SetAutoMovementParams(
              lmqAxis::Max()
            , lmqAxis::Min());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveFR, line) == 0)
    {
        m_robotController->SetAutoMovementParams(
              lmqAxis::Max()
            , lmqAxis::Max());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveF, line) == 0)
    {
        m_robotController->SetAutoMovementParams(
              lmqAxis::Max()
            , lmqAxis::Zero());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveBL, line) == 0)
    {
        m_robotController->SetAutoMovementParams(
              lmqAxis::Min()
            , lmqAxis::Min());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveBR, line) == 0)
    {
        m_robotController->SetAutoMovementParams(
              lmqAxis::Min()
            , lmqAxis::Max());
    }
    else if(lmqRobotConsoleInputController_CMP_STR_ARR(cmdMoveB, line) == 0)
    {
        m_robotController->SetAutoMovementParams(
              lmqAxis::Min()
            , lmqAxis::Zero());
    }

    if(runResetSpeedTimer)
    {
#ifdef ARDUINO
        m_timePointToResetSpeed
            = millis() + lmqRobotConsoleInputController_TIME_TO_RESET_SPEED;
#endif // ARDUINO
    }
}

bool lmqRobotConsoleInputController::IsActive() const
{
    return m_timePointToResetSpeed != ULONG_MAX;
}