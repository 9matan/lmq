#pragma once

#include "lmq/system/Console/lmqConsoleListener.h"

class lmqConsole;
class lmqRobotController;

class lmqConsoleInputController
    : public lmqConsoleListener
{
public:
    lmqConsoleInputController(
        const lmqRobotController* robotController);

    virtual void OnConsoleInput(const char* line) override;

private:
    const lmqRobotController* m_robotController;
};