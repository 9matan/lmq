#include <Arduino.h>

#include "lmq/system/Logging/lmqLogging.h"
#include "lmq/system/Console/lmqConsole.h"

#ifdef ARDUINO_ARCH_AVR
#define lmq_MAX_CONSOLE_BUFFER_SIZE SERIAL_RX_BUFFER_SIZE
#else
#define lmq_MAX_CONSOLE_BUFFER_SIZE 64
#endif // ARDUINO_ARCH_AVR

void lmqConsole::Initialize(unsigned long baud)
{
    Serial.begin(baud);
}

void lmqConsole::Update()
{
    char buffer[lmq_MAX_CONSOLE_BUFFER_SIZE] = {0};

    if(Serial.available() > 0)
    {
        const size_t readCnt = Serial.readBytes(buffer, lmq_MAX_CONSOLE_BUFFER_SIZE);
        const bool isOverflowed = readCnt >= lmq_MAX_CONSOLE_BUFFER_SIZE - 1;
        
        if(isOverflowed)
        {
            lmq_LOG_ERROR(F("[ERR] Console: buffer is overflowed"));
            buffer[0] = '\0';
        }

        if(buffer[0] != '\0')
        {
            if(m_consoleListener)
            {
                Serial.println(buffer);
                m_consoleListener->OnConsoleInput(buffer);
            }
        }
    }
}

void lmqConsole::RegisterConsoleListener(lmqConsoleListener* consoleListener)
{
    if(m_consoleListener)
    {
        lmq_LOG_ERROR(F("[ERR] Console: can't register listener"));
        return;
    }

    m_consoleListener = consoleListener;
}