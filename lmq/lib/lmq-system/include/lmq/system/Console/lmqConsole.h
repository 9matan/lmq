#pragma once

#include "lmq/System/Console/lmqConsoleListener.h"

class lmqConsole
{
public:
    void Initialize(unsigned long baud);
    void Update();

    void RegisterConsoleListener(lmqConsoleListener* consoleListener);

private:
    lmqConsoleListener* m_consoleListener = nullptr;
};