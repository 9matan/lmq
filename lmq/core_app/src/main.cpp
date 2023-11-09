#include <Arduino.h>

#include "lmq/core_app/lmqCoreApp.h"

void setup()
{
    lmq_CORE_APP->Initialize();
}

void loop()
{
    lmq_CORE_APP->Update();
    delay(100);
}