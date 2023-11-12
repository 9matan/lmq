#pragma once

#include <stdint.h>

#include "lmq/engine/MovementController/lmqMovement.h"

class lmqAutoMovementController
{
public:
    virtual ~lmqAutoMovementController() {}

    virtual void SetSpeed(int8_t speed) = 0;
    virtual void SetTurn(int8_t turn) = 0;
};