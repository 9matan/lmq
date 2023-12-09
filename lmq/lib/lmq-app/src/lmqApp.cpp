#include "lmq/app/lmqApp.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif // ARDUINO

#ifdef ARDUINO_ARCH_ESP32
#include <ESP32PWM.h>
#endif // ARDUINO_ARCH_ESP32

#ifdef ARDUINO_ARCH_ESP32
#define NO_GLOBAL_INSTANCES
#include <PS4Controller.h>
#undef NO_GLOBAL_INSTANCES
#else // ARDUINO_ARCH_ESP32
#error "The PS4Controller is not implemented for the platform"
#endif // !ARDUINO_ARCH_ESP32

#include "lmq/system/Console/lmqConsole.h"
#include "lmq/system/Logging/lmqLogging.h"

#include "lmq/engine/InputController/lmqConsoleInputController.h"
#include "lmq/engine/InputController/lmqGamepadControlsState.h"
#include "lmq/engine/InputController/lmqGamepadInputController.h"
#include "lmq/engine/lmqEngine.h"
#include "lmq/engine/Robot/lmqRobot.h"
#include "lmq/engine/Robot/lmqRobotController.h"

#include "lmq/component/MotorDriver/lmqMotorDriver_L298N.h"

#include "lmq/robot/Controllers/lmqRobotAutoMovementController_L298N.h"
#include "lmq/robot/Controllers/lmqRobotManualMovementController_L298N.h"

#include "lmq/app/Robot/lmqRobotBuilder.h"

#ifdef ARDUINO_ARCH_ESP32
static void private_lmqApp_OnPS4ControllerConnected();
static void private_lmqApp_OnPS4ControllerDisconnected();
static lmqGamepadControlsState private_lmqApp_CreateGamepadControlsState(
    PS4Controller*);
#endif // ARDUINO_ARCH_ESP32

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
    InitializeConsoleInputController();
    InitializePS4Controller();
    InitializeGamepadInputController();
}

void lmqApp::InitializeConsoleInputController()
{
    m_consoleInputController = new lmqConsoleInputController(m_robotController);
    m_engine->GetConsole().RegisterConsoleListener(m_consoleInputController);
}

void lmqApp::InitializePS4Controller()
{
#ifdef ARDUINO_ARCH_ESP32
    m_ps4Controller = new PS4Controller();
    m_ps4Controller->begin();
    m_ps4Controller->attachOnConnect(
        private_lmqApp_OnPS4ControllerConnected);
    m_ps4Controller->attachOnDisconnect(
        private_lmqApp_OnPS4ControllerDisconnected);
#endif // ARDUINO_ARCH_ESP32
}

void lmqApp::InitializeGamepadInputController()
{
    m_gamepadInputController = new lmqGamepadInputController(m_robotController);
    m_gamepadInputController->SetStickThreshold(lmq_GAMEPAD_STICK_THRESHOLD);
    m_gamepadInputController->SetTriggerThreshold(lmq_GAMEPAD_TRIGGER_THRESHOLD);
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
    UpdateConsoleInputController();
    UpdateGamepadInputController();
}

void lmqApp::UpdateRobot()
{
    m_robotController->Update();
}

void lmqApp::UpdateConsoleInputController()
{
    m_consoleInputController->Update();
}

void lmqApp::UpdateGamepadInputController()
{
#ifdef ARDUINO_ARCH_ESP32
    if(m_ps4Controller->isConnected())
    {
        const auto gamepadControlsState
            = private_lmqApp_CreateGamepadControlsState(m_ps4Controller);
        m_gamepadInputController->OnGamepadControlsState(gamepadControlsState);
    }
#endif // ARDUINO_ARCH_ESP32
}

#ifdef ARDUINO_ARCH_ESP32
static void private_lmqApp_OnPS4ControllerConnected()
{
    lmq_LOG_INFO("PS4 controller is connected");
}

static void private_lmqApp_OnPS4ControllerDisconnected()
{
    lmq_LOG_INFO("PS4 controller is disconnected");
}

static lmqGamepadControlsState private_lmqApp_CreateGamepadControlsState(
    PS4Controller* ps4Controller)
{
    lmqGamepadControlsState gamepadControlsState;

    gamepadControlsState.m_upPressed = ps4Controller->Up();

    gamepadControlsState.m_leftStickX = ps4Controller->LStickX();
    gamepadControlsState.m_leftStickY = ps4Controller->LStickY();
    gamepadControlsState.m_rightStickX = ps4Controller->RStickX();
    gamepadControlsState.m_rightStickY = ps4Controller->RStickY();
    
    gamepadControlsState.m_l2Value = ps4Controller->L2Value();
    gamepadControlsState.m_r2Value = ps4Controller->R2Value();

    return gamepadControlsState;
}
#endif // ARDUINO_ARCH_ESP32