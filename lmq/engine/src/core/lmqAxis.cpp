#include <Arduino.h>

#include "lmq/core/lmqAxis.h"

lmqAxis::lmqAxis(int8_t value)
    : m_value(value)
{
}

lmqAxis lmqAxis::GetInverted()
{
    if(m_value == 0) return Zero();
    else if(m_value > 0)
    {
        return FromInt8(map(m_value, 1, 127, -1, -128));
    }
    else
    {
        return FromInt8(map(m_value, -1, -128, 1, 127));
    }
}

int8_t lmqAxis::ToInt8() const
{
    return m_value;
}

int8_t lmqAxis::ToInt8(const int8_t minVal, const int8_t maxVal) const
{
    return map(m_value, -128, 127, minVal, maxVal);
}