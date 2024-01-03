#pragma once

#include "lmq/system/Console/lmqConsoleListener.h"

class lmqConsole;
class lmqRobotController;

class lmqRobotConsoleInputController
    : public lmqConsoleListener
{
public:
    lmqRobotConsoleInputController(lmqRobotController* robotController);

    void Update();
    
    virtual void OnConsoleInput(const char* line) override;

    bool IsActive() const;

private:
    unsigned long m_timePointToResetSpeed;
    lmqRobotController* m_robotController;
};