#pragma once

#include "lmq/engine/lmqEngineConfig.h"

class lmqConsole;
class lmqInputSystem;
class lmqPS4Controller;

class lmqEngine
{
public:
    lmqEngine(const lmqEngineConfig& engineConfig);

    void Initialize();
    void Update();

public:
    lmqConsole& GetConsole();
    lmqInputSystem& GetInputSystem();

    lmqPS4Controller* GetPS4Controller();

private:
    lmqEngineConfig m_engineConfig;
    lmqConsole* m_console = nullptr;
    lmqInputSystem* m_inputSystem = nullptr;

    lmqPS4Controller* m_ps4Controller = nullptr;

private:
    void InitializeConsole();
    void InitializeInput();

    void UpdateConsole();
    void UpdateInput();
};