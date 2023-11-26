#pragma once

class lmqRobotAutoMovementController;
class lmqRobotManualMovementController;

class lmqRobot
{
public:
    virtual ~lmqRobot() {}

    virtual lmqRobotAutoMovementController* GetAutoMovementController() = 0;
    virtual lmqRobotManualMovementController* GetManualMovementController() = 0;
};