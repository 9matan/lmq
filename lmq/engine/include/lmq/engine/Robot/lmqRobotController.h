#pragma once

class lmqAutoMovementController;

class lmqRobotController
{
public:
    void SetAutoMovementController(lmqAutoMovementController* autoMovementController);
    lmqAutoMovementController* GetAutoMovementController() const;

private:
    lmqAutoMovementController* m_autoMovementController = nullptr;
};