#include "lmq/engine/Robot/lmqRobotController.h"

void lmqRobotController::SetAutoMovementController(
    lmqAutoMovementController* autoMovementController)
{
    m_autoMovementController = autoMovementController;
}

lmqAutoMovementController* lmqRobotController::GetAutoMovementController() const
{
    return m_autoMovementController;
}

void lmqRobotController::SetManualMovementController(
    lmqManualMovementController* manualMovementController)
{
    m_manualMovementController = manualMovementController;
}

lmqManualMovementController* lmqRobotController::GetManualMovementController() const
{
    return m_manualMovementController;
}