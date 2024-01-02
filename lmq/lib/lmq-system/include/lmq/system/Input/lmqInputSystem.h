#pragma once

#include <bitset>
#include <stdint.h>

#include "lmq/core/lmqAxis.h"

#define lmq_INPUT_SYSTEM_KEYS_COUNT 16
#define lmq_INPUT_SYSTEM_AXISES_COUNT 16

class lmqInputSystem
{
public:
    template<typename TKeyCode>
    void SetIsKeyPressed(const TKeyCode keyCode)
    {
        SetIsKeyPressedInternal((lmqKeyCode)keyCode);
    }
    template<typename TAxisCode>
    void SetAxis(const TAxisCode axisCode, lmqAxis const axis)
    {
        SetAxisInternal((lmqAxisCode)axisCode, axis);
    }

    template<typename TKeyCode>
    bool IsKeyPressed(const TKeyCode keyCode)
    {
        return IsKeyPressedInternal((lmqKeyCode)keyCode);
    }
    template<typename TAxisCode>
    lmqAxis GetAxis(const TAxisCode axisCode)
    {
        return GetAxisInternal((lmqAxisCode)axisCode);
    }

    template<typename TKeyCode>
    void RegisterKeyCodes()
    {
        static_assert(lmq_INPUT_SYSTEM_KEYS_COUNT >= TKeyCode::End);
    }

    template<typename TAxisCode>
    void RegisterAxisCodes()
    {
        static_assert(lmq_INPUT_SYSTEM_AXISES_COUNT >= TAxisCode::End);
    }

    void Update();

private:
    typedef uint8_t lmqKeyCode;
    typedef uint8_t lmqAxisCode;

private:
    std::bitset<lmq_INPUT_SYSTEM_KEYS_COUNT> m_isKeyPressed;
    lmqAxis m_axises[lmq_INPUT_SYSTEM_AXISES_COUNT];

private:
    void SetIsKeyPressedInternal(const lmqKeyCode keyCode);
    void SetAxisInternal(const lmqAxisCode axisCode, lmqAxis const axis);

    bool IsKeyPressedInternal(const lmqKeyCode keyCode) const;
    lmqAxis GetAxisInternal(const lmqAxisCode axisCode) const;
};