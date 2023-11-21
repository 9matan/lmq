#pragma once

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

private:
    lmqEngineConfig m_engineConfig;
    lmqConsole* m_console = nullptr;
};