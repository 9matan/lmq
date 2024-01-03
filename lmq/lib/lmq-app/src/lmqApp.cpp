#include "lmq/app/lmqApp.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif // ARDUINO

#ifdef ARDUINO_ARCH_ESP32
#include <ESP32PWM.h>
#endif // ARDUINO_ARCH_ESP32

#include "lmq/system/Console/lmqConsole.h"
#include "lmq/system/Input/Controller/lmqPS4Controller.h"
#include "lmq/system/Logging/lmqLogging.h"

#include "lmq/engine/lmqEngine.h"
#include "lmq/engine/Robot/lmqRobot.h"
#include "lmq/engine/Robot/lmqRobotController.h"

#include "lmq/component/MotorDriver/lmqMotorDriver_L298N.h"

#include "lmq/robot/Controllers/lmqRobotAutoMovementController_L298N.h"
#include "lmq/robot/Controllers/lmqRobotManualMovementController_L298N.h"

#include "lmq/app/Robot/lmqRobotBuilder.h"
#include "lmq/app/Robot/lmqRobotConsoleInputController.h"
#include "lmq/app/Robot/lmqRobotPS4InputController.h"

lmqApp* lmqApp::GetInstance()
{
    static lmqApp app;
    return &app;
}

void lmqApp::Initialize()
{
    InitializeExternalLibs();
    InitializeEngine();
    InitializeRobot();
    InitializeInputControllers();

    lmq_LOG_INFO("App is initialized");
}

void lmqApp::InitializeExternalLibs()
{
#ifdef ARDUINO_ARCH_ESP32
    ESP32PWM::allocateTimer(0);
#endif // ARDUINO_ARCH_ESP32
}

void lmqApp::InitializeEngine()
{
    lmqEngineConfig engineConfig;
    engineConfig.m_consoleBaud = lmq_CONSOLE_BAUD;

    m_engine = new lmqEngine(engineConfig);
    m_engine->Initialize();
}

void lmqApp::InitializeRobot()
{
    m_robot = lmqBuildDefaultRobot();
    m_robotController = new lmqRobotController(m_robot);
}

void lmqApp::InitializeInputControllers()
{
    InitializeRobotPS4InputController();
    InitializeRobotConsoleInputController();
}

void lmqApp::InitializeRobotPS4InputController()
{
#if lmq_PS4_CONTROLLER_SUPPORTED
    auto ps4Controller = m_engine->GetPS4Controller();
    ps4Controller->SetStickThreshold(lmq_GAMEPAD_STICK_THRESHOLD);
    ps4Controller->SetTriggerThreshold(lmq_GAMEPAD_TRIGGER_THRESHOLD);

    m_robotPS4InputController = new lmqRobotPS4InputController(
          &(m_engine->GetInputSystem())
        , m_robotController
    );
#endif // lmq_PS4_CONTROLLER_SUPPORTED
}

void lmqApp::InitializeRobotConsoleInputController()
{
    m_robotConsoleInputController = new lmqRobotConsoleInputController(m_robotController);
    m_engine->GetConsole().RegisterConsoleListener(m_robotConsoleInputController);
}

void lmqApp::Update()
{
    UpdateEngine();
    UpdateInputControllers();
    UpdateRobot();
}

void lmqApp::UpdateEngine()
{
    m_engine->Update();
}

void lmqApp::UpdateInputControllers()
{
    m_robotConsoleInputController->Update();
#if lmq_PS4_CONTROLLER_SUPPORTED
    if(!m_robotConsoleInputController->IsActive())
    {
        m_robotPS4InputController->Update();
    }
#endif // lmq_PS4_CONTROLLER_SUPPORTED
}

void lmqApp::UpdateRobot()
{
    m_robotController->Update();
}