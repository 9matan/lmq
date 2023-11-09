#pragma once

#include <stdint.h>

#define lmq_MOVEMENT_TURN_LEFT -127
#define lmq_MOVEMENT_TURN_RIGHT 127
#define lmq_MOVEMENT_TURN_STRAIGHT 0

#define lmq_MOVEMENT_SPEED_FORWARD 127
#define lmq_MOVEMENT_SPEED_BACKWARD -127
#define lmq_MOVEMENT_SPEED_STOP 0

class lmqAutoMovementController
{
public:
    virtual ~lmqAutoMovementController() {}

    virtual void SetSpeed(int8_t speed) = 0;
    virtual void SetTurn(int8_t turn) = 0;
};