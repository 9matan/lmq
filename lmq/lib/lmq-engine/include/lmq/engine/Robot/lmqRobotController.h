#pragma once

#include "lmq/core/lmqAxis.h"

class lmqRobot;

class lmqRobotAutoMovementController;
class lmqRobotHeadController;
class lmqRobotManualMovementController;

class lmqRobotController
{
public:
    lmqRobotController(lmqRobot* robot);

    void Update();

    void SetAutoMovementParams(
          const lmqAxis speedAxis
        , const lmqAxis turnAxis);
    void SetManualMovementParams(
          const lmqAxis leftChannelSpeedAxis
        , const lmqAxis rightChannelSpeedAxis);

    void RotateHead(const lmqAxis rotationAxis);

private:
    lmqRobotAutoMovementController* m_autoMovementController = nullptr;
    lmqRobotManualMovementController* m_manualMovementController = nullptr;
    lmqRobotHeadController* m_headController = nullptr;
};