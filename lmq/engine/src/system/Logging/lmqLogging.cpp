#include <Arduino.h>

#include "lmq/system/Logging/lmqLogging.h"

#ifdef ARDUINO

void lmqLogDebug(const __FlashStringHelper* ifsh)
{
    Serial.println(ifsh);
}

void lmqLogInfo(const __FlashStringHelper* ifsh)
{
    Serial.println(ifsh);
}

void lmqLogWarning(const __FlashStringHelper* ifsh)
{
    Serial.println(ifsh);
}

void lmqLogError(const __FlashStringHelper* ifsh)
{
    Serial.println(ifsh);
}

void lmqLogDebug(const char* str)
{
    Serial.println(str);
}

void lmqLogInfo(const char* str)
{
    Serial.println(str);
}

void lmqLogWarning(const char* str)
{
    Serial.println(str);
}

void lmqLogError(const char* str)
{
    Serial.println(str);
}

#endif // ARDUINO