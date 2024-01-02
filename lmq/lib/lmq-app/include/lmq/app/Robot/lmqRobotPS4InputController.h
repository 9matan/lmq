#pragma once

class lmqInputSystem;
class lmqRobotController;

class lmqRobotPS4InputController
{
public:
    lmqRobotPS4InputController(
          lmqInputSystem* inputSystem
        , lmqRobotController* robotController);

    void Update();

private:
    lmqInputSystem* m_inputSystem;
    lmqRobotController* m_robotController;
};