#pragma once

#include <stdint.h>

class lmqRobotHeadController
{
public:
    virtual ~lmqRobotHeadController() {}

    virtual void Rotate(const int8_t speed) = 0;
};