#pragma once

#include <stdint.h>

#include "lmq/engine/Robot/lmqRobotMovement.h"

class lmqRobotAutoMovementController
{
public:
    virtual ~lmqRobotAutoMovementController() {}

    virtual void SetSpeed(int8_t speed) = 0;
    virtual void SetTurn(int8_t turn) = 0;
};