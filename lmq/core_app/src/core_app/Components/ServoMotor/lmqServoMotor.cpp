#include "lmq/core_app/Components/ServoMotor/lmqServoMotor.h"

#ifdef ARDUINO_ARCH_ESP32
#include <ESP32Servo.h>
#else // ARDUINO_ARCH_ESP32
#error "The servo motor is not implemented for the platform"
#endif // !ARDUINO_ARCH_ESP32

lmqServoMotor::lmqServoMotor(
      const uint16_t frequency
    , const uint16_t minPulseWidth
    , const uint16_t maxPulseWidth
    , const uint8_t pin)
{
    m_servo = new Servo();
    m_servo->setPeriodHertz(frequency);
    m_servo->attach(pin, minPulseWidth, maxPulseWidth);
}

lmqServoMotor::~lmqServoMotor()
{
    delete m_servo;
}

void lmqServoMotor::RotateTo(const uint8_t angles)
{
    m_servo->write(angles);
}