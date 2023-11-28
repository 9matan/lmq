#pragma once

#include <stdint.h>

#include "lmq/engine/Robot/lmqRobotMovement.h"

class lmqRobotManualMovementController
{
public:
    virtual ~lmqRobotManualMovementController() {}

    virtual void SetLChannelSpeed(const int8_t speed) = 0;
    virtual void SetRChannelSpeed(const int8_t speed) = 0;
};