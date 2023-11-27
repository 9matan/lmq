#pragma once

class lmqRobotAutoMovementController;
class lmqRobotManualMovementController;
class lmqRobotHeadController;

class lmqRobot
{
public:
    virtual ~lmqRobot() {}

    virtual lmqRobotAutoMovementController* GetAutoMovementController() = 0;
    virtual lmqRobotManualMovementController* GetManualMovementController() = 0;
    virtual lmqRobotHeadController* GetHeadController() = 0;
};