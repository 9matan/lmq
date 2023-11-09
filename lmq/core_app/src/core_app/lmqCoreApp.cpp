#include <Arduino.h>

#ifdef ESP32
#define NO_GLOBAL_INSTANCES
#include <PS4Controller.h>
#undef NO_GLOBAL_INSTANCES
#endif // ESP32

#include "lmq/core_app/lmqCoreApp.h"

#include "lmq/system/Console/lmqConsole.h"
#include "lmq/system/Logging/lmqLogging.h"

#include "lmq/engine/InputController/lmqConsoleInputController.h"
#include "lmq/engine/InputController/lmqGamepadInputController.h"
#include "lmq/engine/InputController/lmqGamepadState.h"
#include "lmq/engine/lmqEngine.h"
#include "lmq/engine/Robot/lmqRobot.h"
#include "lmq/engine/Robot/lmqRobotController.h"
#include "lmq/engine/MotorDriver/lmqMotorDriver_L298N.h"
#include "lmq/engine/MovementController/lmqAutoMovementController_L298N.h"

#include "lmq/core_app/Robot/lmqRobotBuilder.h"

static void private_lmqCoreApp_OnPS4ControllerConnected();
static void private_lmqCoreApp_OnPS4ControllerDisconnected();
static lmqGamepadState private_lmqCoreApp_CreateGamepadState(PS4Controller*);

lmqCoreApp* lmqCoreApp::GetInstance()
{
    static lmqCoreApp app;
    return &app;
}

void lmqCoreApp::Initialize()
{
    InitializeEngine();
    InitializeRobot();
    InitializeInputControllers();

    lmq_LOG_INFO("App is initialized");
}

void lmqCoreApp::InitializeEngine()
{
    lmqEngineConfig engineConfig;
    engineConfig.m_consoleBaud = lmq_CONSOLE_BAUD;

    m_engine = new lmqEngine(engineConfig);
    m_engine->Initialize();
}

void lmqCoreApp::InitializeRobot()
{
    m_robot = lmqBuildDefaultRobot();

    m_robotController = new lmqRobotController();
    m_robotController->SetAutoMovementController(
        m_robot->GetAutoMovementController());
}

void lmqCoreApp::InitializeInputControllers()
{
    m_consoleInputController = new lmqConsoleInputController(m_robotController);
    m_engine->GetConsole().RegisterConsoleListener(m_consoleInputController);

    m_ps4Controller = new PS4Controller();
    m_ps4Controller->begin();
    m_ps4Controller->attachOnConnect(
        private_lmqCoreApp_OnPS4ControllerConnected);
    m_ps4Controller->attachOnDisconnect(
        private_lmqCoreApp_OnPS4ControllerDisconnected);
    m_gamepadInputController = new lmqGamepadInputController(m_robotController);
    m_gamepadInputController->SetStickThreshold(lmq_GAMEPAD_STICK_THRESHOLD);
    m_gamepadInputController->SetTriggerThreshold(lmq_GAMEPAD_TRIGGER_THRESHOLD);
}

void lmqCoreApp::Update()
{
    UpdateInputControllers();
    UpdateEngine();
}

void lmqCoreApp::UpdateInputControllers()
{
    m_consoleInputController->Update();

    if(m_ps4Controller->isConnected())
    {
        const auto gamepadState = private_lmqCoreApp_CreateGamepadState(
            m_ps4Controller);
        m_gamepadInputController->OnGamepadState(gamepadState);
    }
}

void lmqCoreApp::UpdateEngine()
{
    m_engine->Update();
}

void lmqCoreApp::OnPS4ControllerConnected()
{
    lmq_LOG_INFO("PS4 controller is connected");
    Serial.printf("\tBattery: %.2f%", (float)m_ps4Controller->Battery() / 2.55f);
}

static void private_lmqCoreApp_OnPS4ControllerConnected()
{
    lmq_CORE_APP->OnPS4ControllerConnected();
}

static void private_lmqCoreApp_OnPS4ControllerDisconnected()
{
    lmq_LOG_INFO("PS4 controller is disconnected");
}

static lmqGamepadState private_lmqCoreApp_CreateGamepadState(
    PS4Controller* ps4Controller)
{
    lmqGamepadState gamepadState;

    gamepadState.m_leftStickX = ps4Controller->LStickX();
    gamepadState.m_leftStickY = ps4Controller->LStickY();
    gamepadState.m_rightStickX = ps4Controller->RStickX();
    gamepadState.m_rightStickY = ps4Controller->RStickY();
    
    gamepadState.m_l2Value = ps4Controller->L2Value();
    gamepadState.m_r2Value = ps4Controller->R2Value();

    return gamepadState;
}