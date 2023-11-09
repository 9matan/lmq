#pragma once

#include <stdint.h>

struct lmqGamepadState;
class lmqRobotController;

class lmqGamepadInputController
{
public:
    lmqGamepadInputController(
        lmqRobotController* robotController);

    void OnGamepadState(const lmqGamepadState& gamepadState);

    void SetStickThreshold(const uint8_t stickThreshold);

    void SetTriggerThreshold(const uint8_t triggerThreshold);

private:
    lmqRobotController* m_robotController;
    uint8_t m_stickThreshold;
    uint8_t m_triggerThreshold;
};