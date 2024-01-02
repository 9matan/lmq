#pragma once

#define lmq_DEFAULT_CONSOLE_BAUD 115200
#define lmq_DEFAULT_PS4_CONTROLLER_ENABLED 1

struct lmqEngineConfig
{
    unsigned long m_consoleBaud = lmq_DEFAULT_CONSOLE_BAUD;
    bool m_isPS4ControllerEnabled = lmq_DEFAULT_PS4_CONTROLLER_ENABLED;
};