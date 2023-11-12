#pragma once

#include <stdint.h>

#include "lmq/engine/MovementController/lmqMovement.h"

class lmqManualMovementController
{
public:
    virtual ~lmqManualMovementController() {}

    virtual void SetLChannelSpeed(const int8_t speed) = 0;
    virtual void SetRChannelSpeed(const int8_t speed) = 0;
};