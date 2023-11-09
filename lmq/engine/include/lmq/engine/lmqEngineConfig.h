#pragma once

#define lmq_DEFAULT_CONSOLE_BAUD 115200

struct lmqEngineConfig
{
    unsigned long m_consoleBaud = lmq_DEFAULT_CONSOLE_BAUD;
};