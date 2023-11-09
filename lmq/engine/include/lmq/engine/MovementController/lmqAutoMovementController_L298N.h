#pragma once

#include <stdint.h>

#include "lmq/engine/MovementController/lmqAutoMovementController.h"

class lmqMotorDriver_L298N;

class lmqAutoMovementController_L298N
    : public lmqAutoMovementController
{
public:
    lmqAutoMovementController_L298N(
        lmqMotorDriver_L298N* motorDriver);

    virtual void SetSpeed(int8_t speed) override;
    virtual void SetTurn(int8_t turn) override;

private:
    lmqMotorDriver_L298N* m_motorDriver;
    int8_t m_speed;
    int8_t m_turn;

private:
    void UpdateEnginePower();
};