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
    enum ELayout
    {
        LAYOUT_AUTO_MOVE,
        LAYOUT_MANUAL_MOVE
    };

private:
    lmqInputSystem* m_inputSystem;
    lmqRobotController* m_robotController;
    ELayout m_layout;

private:
    void UpdateCurrentLayout();
    void UpdateAutoMoveLayout();
    void UpdateManualMoveLayout();
    void UpdateHead();
    void SwitchLayout();
};