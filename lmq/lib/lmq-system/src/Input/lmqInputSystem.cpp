#include "lmq/system/Input/lmqInputSystem.h"

void lmqInputSystem::SetIsKeyPressedInternal(const lmqKeyCode keyCode)
{
    m_isKeyPressed.set(keyCode, true);
}

void lmqInputSystem::SetAxisInternal(const lmqAxisCode axisCode, lmqAxis const axis)
{
    m_axises[axisCode] = axis;
}

bool lmqInputSystem::IsKeyPressedInternal(const lmqKeyCode keyCode) const
{
    return m_isKeyPressed.test(keyCode);
}

lmqAxis lmqInputSystem::GetAxisInternal(const lmqAxisCode axisCode) const
{
    return m_axises[axisCode];
}

void lmqInputSystem::Update()
{
    m_isKeyPressed.reset();
}