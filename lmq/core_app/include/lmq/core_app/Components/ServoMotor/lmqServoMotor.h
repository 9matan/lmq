#pragma once

#include <stdint.h>

class Servo;

class lmqServoMotor
{
public:
    lmqServoMotor(
          const uint16_t frequency
        , const uint16_t minPulseWidth
        , const uint16_t maxPulseWidth
        , const uint8_t pin);
    ~lmqServoMotor();

    /**
     * @param angles [0;180]
    */
    void RotateTo(const uint8_t angles);

private:
    Servo* m_servo;
};