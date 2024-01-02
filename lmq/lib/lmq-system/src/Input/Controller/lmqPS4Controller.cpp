#include "lmq/system/Input/Controller/lmqPS4Controller.h"

#ifdef lmq_PS4_CONTROLLER_SUPPORTED
#ifdef ARDUINO_ARCH_ESP32
#include <PS4Controller.h>
#endif // ARDUINO_ARCH_ESP32

#include "lmq/core/lmqLerp.h"

#include "lmq/system/Input/Controller/lmqPS4ControllerKeyCodes.h"
#include "lmq/system/Input/lmqInputSystem.h"
#include "lmq/system/Logging/lmqLogging.h"

static void private_lmqPS4Controller_OnConnected();
static void private_lmqPS4Controller_OnDisconnected();

lmqPS4Controller::lmqPS4Controller(lmqInputSystem* inputSystem)
    : m_inputSystem(inputSystem)
    , m_ps4Controller(new PS4Controller)
{
    m_ps4Controller->begin();
    m_ps4Controller->attachOnConnect(private_lmqPS4Controller_OnConnected);
    m_ps4Controller->attachOnDisconnect(private_lmqPS4Controller_OnDisconnected);
}

lmqPS4Controller::~lmqPS4Controller()
{
    m_ps4Controller->end();
    delete m_ps4Controller;
}

void lmqPS4Controller::Update()
{
    if(!m_ps4Controller->isConnected())
        return;

    if(m_ps4Controller->Up()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Up);
    if(m_ps4Controller->Down()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Down);
    if(m_ps4Controller->Left()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Left);
    if(m_ps4Controller->Right()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Right);

    if(m_ps4Controller->Cross()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Cross);
    if(m_ps4Controller->Circle()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Circle);
    if(m_ps4Controller->Triangle()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Triangle);
    if(m_ps4Controller->Square()) m_inputSystem->SetIsKeyPressed(lmqPS4KeyCode::Square);

    m_inputSystem->SetAxis(lmqPS4AxisCode::LeftStickX, GetAxisFromStick(m_ps4Controller->LStickX()));
    m_inputSystem->SetAxis(lmqPS4AxisCode::LeftStickY, GetAxisFromStick(m_ps4Controller->LStickY()));
    m_inputSystem->SetAxis(lmqPS4AxisCode::RightStickX, GetAxisFromStick(m_ps4Controller->RStickX()));
    m_inputSystem->SetAxis(lmqPS4AxisCode::RightStickY, GetAxisFromStick(m_ps4Controller->RStickY()));

    m_inputSystem->SetAxis(lmqPS4AxisCode::L2, GetAxisFromTrigger(m_ps4Controller->L2Value()));
    m_inputSystem->SetAxis(lmqPS4AxisCode::R2, GetAxisFromTrigger(m_ps4Controller->R2Value()));
}

void lmqPS4Controller::SetStickThreshold(const uint8_t stickThreshold)
{
    m_stickThreshold = stickThreshold;
}

void lmqPS4Controller::SetTriggerThreshold(const uint8_t triggerThreshold)
{
    m_triggerThreshold = triggerThreshold;
}

lmqAxis lmqPS4Controller::GetAxisFromStick(
      const int8_t stickInput) const
{
    if(abs(stickInput) < m_stickThreshold / 2) return lmqAxis::Zero();

    return lmqAxis::FromInt8(
        stickInput >= 0
        ? lmqMapValue(stickInput, m_stickThreshold / 2, 127, 0, 127)
        : lmqMapValue(stickInput, -m_stickThreshold / 2, -128, -1, -128));
}

lmqAxis lmqPS4Controller::GetAxisFromTrigger(
    const uint8_t triggerInput) const
{
    if(triggerInput < m_triggerThreshold) return lmqAxis::Zero();
    
    return lmqAxis::FromInt8(
        lmqMapValue(triggerInput, m_triggerThreshold, 255, 0, 255) / 2);
}

static void private_lmqPS4Controller_OnConnected()
{
    lmq_LOG_INFO("PS4 controller is connected");
}

static void private_lmqPS4Controller_OnDisconnected()
{
    lmq_LOG_INFO("PS4 controller is disconnected");
}

#endif // lmq_PS4_CONTROLLER_SUPPORTED