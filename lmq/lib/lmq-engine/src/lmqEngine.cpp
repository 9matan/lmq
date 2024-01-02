#include "lmq/engine/lmqEngine.h"

#include "lmq/system/Console/lmqConsole.h"
#include "lmq/system/Input/Controller/lmqPS4Controller.h"
#include "lmq/system/Input/lmqInputSystem.h"

lmqEngine::lmqEngine(const lmqEngineConfig& engineConfig)
    : m_engineConfig(engineConfig)
{
}

void lmqEngine::Initialize()
{
    InitializeConsole();
    InitializeInput();
}

void lmqEngine::InitializeConsole()
{
    m_console = new lmqConsole(m_engineConfig.m_consoleBaud);
}

void lmqEngine::InitializeInput()
{
    m_inputSystem = new lmqInputSystem();
#if lmq_PS4_CONTROLLER_SUPPORTED
    if(m_engineConfig.m_isPS4ControllerEnabled)
    {
        m_ps4Controller = new lmqPS4Controller(m_inputSystem);
    }
#endif // lmq_PS4_CONTROLLER_SUPPORTED
}

void lmqEngine::Update()
{
    UpdateConsole();
    UpdateInput();
}

void lmqEngine::UpdateConsole()
{
    m_console->Update();
}

void lmqEngine::UpdateInput()
{
    m_inputSystem->Update();
#if lmq_PS4_CONTROLLER_SUPPORTED
    m_ps4Controller->Update();
#endif // lmq_PS4_CONTROLLER_SUPPORTED
}

lmqConsole& lmqEngine::GetConsole() { return *m_console; }
lmqInputSystem& lmqEngine::GetInputSystem() { return *m_inputSystem; }
lmqPS4Controller* lmqEngine::GetPS4Controller() { return m_ps4Controller; }