#pragma once

#ifdef ARDUINO_ARCH_ESP32
    #define lmq_PS4_CONTROLLER_SUPPORTED 1
#endif // ARDUINO_ARCH_ESP32

#ifdef lmq_PS4_CONTROLLER_SUPPORTED

#include <stdint.h>

#include "lmq/core/lmqAxis.h"

class lmqInputSystem;
class PS4Controller;

class lmqPS4Controller
{
public:
    lmqPS4Controller(lmqInputSystem* inputSystem);
    ~lmqPS4Controller();

    void Update();

    void SetStickThreshold(const uint8_t stickThreshold);
    void SetTriggerThreshold(const uint8_t triggerThreshold);

private:
    lmqInputSystem* m_inputSystem;
    PS4Controller* m_ps4Controller;
    uint8_t m_stickThreshold;
    uint8_t m_triggerThreshold;

private:
    lmqAxis GetAxisFromStick(const int8_t stickInput) const;
    lmqAxis GetAxisFromTrigger(const uint8_t triggerInput) const;
};
#endif // lmq_PS4_CONTROLLER_SUPPORTED