#pragma once

#include "lmq/system/Console/lmqConsoleListener.h"

class lmqConsole;
class lmqRobotController;

class lmqConsoleInputController
    : public lmqConsoleListener
{
public:
    lmqConsoleInputController(const lmqRobotController* robotController);

    void Update();
    
    virtual void OnConsoleInput(const char* line) override;

private:
    unsigned long m_timePointToResetSpeed;
    const lmqRobotController* m_robotController;
};