#pragma once

class lmqAutoMovementController;
class lmqManualMovementController;

class lmqRobot
{
public:
    virtual ~lmqRobot() {}

    virtual lmqAutoMovementController* GetAutoMovementController() = 0;
    virtual lmqManualMovementController* GetManualMovementController() = 0;
};