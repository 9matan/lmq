#pragma once

#include <stdint.h>

class lmqAxis
{
public:
    static inline lmqAxis Zero() { return lmqAxis(int8_t(0)); }
    static inline lmqAxis FromInt8(const int8_t value) { return lmqAxis(value); }
    static inline lmqAxis Max() { return lmqAxis(int8_t(127)); }
    static inline lmqAxis Min() { return lmqAxis(int8_t(-128)); }

public:
    lmqAxis();
    lmqAxis GetInverted();

    int8_t ToInt8() const;
    int8_t ToInt8(const int8_t minVal, const int8_t maxVal) const;

    lmqAxis operator+(lmqAxis const other) const;

private:
    int8_t m_value;

private:
    lmqAxis(const int8_t value);
};