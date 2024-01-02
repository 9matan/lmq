#pragma once

#include "lmq/app/lmqAppConfig.h"

#include "lmq/system/Console/lmqConsoleListener.h"

#define lmq_CORE_APP lmqApp::GetInstance()

class lmqEngine;

class lmqRobot;
class lmqRobotController;

class lmqRobotConsoleInputController;
class lmqRobotPS4InputController;

class lmqApp
{
public:
    static lmqApp* GetInstance();

public:
    void Initialize();
    
    void Update();

private:
    lmqEngine* m_engine = nullptr;
    lmqRobot* m_robot = nullptr;
    lmqRobotController* m_robotController = nullptr;

    lmqRobotConsoleInputController* m_robotConsoleInputController = nullptr;
    lmqRobotPS4InputController* m_robotPS4InputController = nullptr;

private:
    void InitializeExternalLibs();
    void InitializeEngine();
    void InitializeRobot();
    void InitializeInputControllers();

    void InitializeRobotPS4InputController();
    void InitializeRobotConsoleInputController();

    void UpdateInputControllers();
    void UpdateEngine();
    void UpdateRobot();
};