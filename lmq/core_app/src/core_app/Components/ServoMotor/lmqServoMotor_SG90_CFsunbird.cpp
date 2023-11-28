#include "lmq/core_app/Components/ServoMotor/lmqServoMotor_SG90_CFsunbird.h"

#define lmqServoMotor_SG90_CFsunbird_FREQUENCY 50
#define lmqServoMotor_SG90_CFsunbird_MIN_PULSE_WIDTH 500
#define lmqServoMotor_SG90_CFsunbird_MAX_PULSE_WIDTH 2500

lmqServoMotor_SG90_CFsunbird::lmqServoMotor_SG90_CFsunbird(const uint8_t pin)
    : lmqServoMotor(
          lmqServoMotor_SG90_CFsunbird_FREQUENCY
        , lmqServoMotor_SG90_CFsunbird_MIN_PULSE_WIDTH
        , lmqServoMotor_SG90_CFsunbird_MAX_PULSE_WIDTH
        , pin)
{}