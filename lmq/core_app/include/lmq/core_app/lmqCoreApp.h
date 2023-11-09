#pragma once

#include "lmq/core_app/lmqCoreAppConfig.h"

#include "lmq/system/Console/lmqConsoleListener.h"

#define lmq_CORE_APP lmqCoreApp::GetInstance()

class PS4Controller;

class lmqEngine;

class lmqConsoleInputController;
class lmqGamepadInputController;
class lmqRobot;
class lmqRobotController;

class lmqCoreApp
{
public:
    static lmqCoreApp* GetInstance();

public:
    void Initialize();
    
    void Update();
    void UpdateInputControllers();
    void UpdateEngine();

    void ResetRobotInput();

    void OnPS4ControllerConnected();

private:
    lmqEngine* m_engine = nullptr;
    lmqRobot* m_robot = nullptr;
    lmqRobotController* m_robotController = nullptr;

    PS4Controller* m_ps4Controller = nullptr;
    lmqGamepadInputController* m_gamepadInputController = nullptr;
    lmqConsoleInputController* m_consoleInputController = nullptr;

private:
    void InitializeEngine();
    void InitializeRobot();
    void InitializeInputControllers();
};