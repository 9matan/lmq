#pragma once

#include "lmq/app/lmqCoreAppConfig.h"

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

private:
    lmqEngine* m_engine = nullptr;
    lmqRobot* m_robot = nullptr;
    lmqRobotController* m_robotController = nullptr;

    PS4Controller* m_ps4Controller = nullptr;
    lmqGamepadInputController* m_gamepadInputController = nullptr;
    lmqConsoleInputController* m_consoleInputController = nullptr;

private:
    void InitializeExternalLibs();
    void InitializeEngine();
    void InitializeRobot();
    void InitializeInputControllers();

    void InitializeConsoleInputController();
    void InitializePS4Controller();
    void InitializeGamepadInputController();

    void UpdateInputControllers();
    void UpdateEngine();
    void UpdateRobot();

    void UpdateConsoleInputController();
    void UpdateGamepadInputController();
};