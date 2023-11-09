#pragma once

class lmqAutoMovementController;

class lmqRobot
{
public:
    virtual ~lmqRobot() {}

    virtual lmqAutoMovementController* GetAutoMovementController() = 0;
};