#pragma once

class lmqAutoMovementController;
class lmqManualMovementController;

class lmqRobotController
{
public:
    void SetAutoMovementController(
        lmqAutoMovementController* autoMovementController);
    lmqAutoMovementController* GetAutoMovementController() const;

    void SetManualMovementController(
        lmqManualMovementController* manualMovementController);
    lmqManualMovementController* GetManualMovementController() const;

private:
    lmqAutoMovementController* m_autoMovementController = nullptr;
    lmqManualMovementController* m_manualMovementController = nullptr;
};