#include "lmq/engine/lmqEngine.h"

#ifdef ARDUINO_ARCH_AVR
#include <MemoryUsage.h>
#endif // ARDUINO_ARCH_AVR

#include "lmq/system/Console/lmqConsole.h"

lmqEngine::lmqEngine(const lmqEngineConfig& engineConfig)
    : m_engineConfig(engineConfig)
{
}

void lmqEngine::Initialize()
{
    m_console = new lmqConsole();
    m_console->Initialize(m_engineConfig.m_consoleBaud);
    m_tasksScheduler = new Timer<>();
#ifdef ARDUINO_ARCH_AVR
    SRamDisplay();
#endif // ARDUINO_ARCH_AVR
}

void lmqEngine::Update()
{
    m_console->Update();
    m_tasksScheduler->tick();
}

lmqConsole& lmqEngine::GetConsole() const { return *m_console; }

Timer<>& lmqEngine::GetTasksScheduler() const { return *m_tasksScheduler; }