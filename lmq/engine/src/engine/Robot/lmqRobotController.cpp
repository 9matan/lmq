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