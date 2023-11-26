#pragma once

#include "lmq/core/lmqAxis.h"

class lmqRobot;

class lmqRobotAutoMovementController;
class lmqRobotManualMovementController;

class lmqRobotController
{
public:
    lmqRobotController(lmqRobot* robot);

    void Update();

    void SwitchMovementMode();
    void SetTurn(const lmqAxis axis);
    void SetSpeed(const lmqAxis axis);
    void SetLeftChannelSpeed(const lmqAxis axis);
    void SetRightChannelSpeed(const lmqAxis axis);

private:
    enum EMovementMode
    {
        MOVEMENT_MODE_NONE = 0,
        MOVEMENT_MODE_AUTO,
        MOVEMENT_MODE_MANUAL
    };

private:
    EMovementMode m_movementMode;
    lmqRobotAutoMovementController* m_autoMovementController = nullptr;
    lmqRobotManualMovementController* m_manualMovementController = nullptr;

    union
    {
        lmqAxis m_turnAxis;
        lmqAxis m_leftChannelSpeedAxis;
    };
    
    union
    {
        lmqAxis m_speedAxis;
        lmqAxis m_rightChannelSpeedAxis;
    };
    
private:
    void UpdateAutoMovementMode();
    void UpdateManualMovementMode();
};