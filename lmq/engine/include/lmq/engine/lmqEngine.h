#pragma once

#include <arduino-timer.h>

#include "lmq/engine/lmqEngineConfig.h"

class lmqConsole;

class lmqEngine
{
public:
    lmqEngine(const lmqEngineConfig& engineConfig);

    void Initialize();
    void Update();

public:
    lmqConsole& GetConsole() const;
    Timer<>& GetTasksScheduler() const;

private:
    lmqEngineConfig m_engineConfig;
    Timer<>* m_tasksScheduler = nullptr;
    lmqConsole* m_console = nullptr;
};