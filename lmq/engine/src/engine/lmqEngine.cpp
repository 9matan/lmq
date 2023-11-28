#include "lmq/engine/lmqEngine.h"

#include "lmq/system/Console/lmqConsole.h"

lmqEngine::lmqEngine(const lmqEngineConfig& engineConfig)
    : m_engineConfig(engineConfig)
{
}

void lmqEngine::Initialize()
{
    m_console = new lmqConsole();
    m_console->Initialize(m_engineConfig.m_consoleBaud);
}

void lmqEngine::Update()
{
    m_console->Update();
}

lmqConsole& lmqEngine::GetConsole() const { return *m_console; }