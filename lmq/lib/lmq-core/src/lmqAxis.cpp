#include "lmq/core/lmqAxis.h"

#include <limits.h>

#include "lmq/core/lmqLerp.h"

lmqAxis::lmqAxis()
    : m_value(0)
{}

lmqAxis::lmqAxis(int8_t value)
    : m_value(value)
{}

lmqAxis lmqAxis::GetInverted()
{
    if(m_value == 0) return Zero();
    else if(m_value > 0)
    {
        return FromInt8(lmqMapValue(m_value, 1, SCHAR_MAX, -1, SCHAR_MIN));
    }
    else
    {
        return FromInt8(lmqMapValue(m_value, -1, SCHAR_MIN, 1, SCHAR_MAX));
    }
}

int8_t lmqAxis::ToInt8() const
{
    return m_value;
}

int8_t lmqAxis::ToInt8(const int8_t minVal, const int8_t maxVal) const
{
    return lmqMapValue(m_value, SCHAR_MIN, SCHAR_MAX, minVal, maxVal);
}

lmqAxis lmqAxis::operator+(lmqAxis const other) const
{
    long sum = (long)m_value + (long)other.m_value;
    if(sum > SCHAR_MAX) sum = SCHAR_MAX;
    else if(sum < SCHAR_MIN) sum = SCHAR_MIN;
    return lmqAxis::FromInt8(sum);
}