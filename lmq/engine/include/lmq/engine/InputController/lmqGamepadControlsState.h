#pragma once

#include <stdint.h>

struct lmqGamepadControlsState
{
    bool m_upPressed = false;

    int8_t m_leftStickX = 0;
    int8_t m_leftStickY = 0;
    int8_t m_rightStickX = 0;
    int8_t m_rightStickY = 0;

    uint8_t m_l2Value = 0;
    uint8_t m_r2Value = 0;
};