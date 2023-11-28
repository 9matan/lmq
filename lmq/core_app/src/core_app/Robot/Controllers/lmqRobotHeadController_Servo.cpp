#include "lmq/core_app/Robot/Controllers/lmqRobotHeadController_Servo.h"

#include <algorithm>

#include "lmq/core/lmqLerp.h"
#include "lmq/core_app/Components/ServoMotor/lmqServoMotor.h"

lmqRobotHeadController_Servo::lmqRobotHeadController_Servo(
      lmqServoMotor* servo
    , const uint8_t initAngle
    , const uint8_t maxAngleSpeed)
    : m_servo(servo)
    , m_currentAngle(std::min(initAngle, (uint8_t)180))
    , m_maxAngleSpeed(maxAngleSpeed)
{
    m_servo->RotateTo(m_currentAngle);
}

void lmqRobotHeadController_Servo::Rotate(const int8_t speed)
{
    if(speed == 0)
    {
        return;
    }

    const long deltaAngle = lmqMapValue(speed
            , -128, 127
            , -(long)m_maxAngleSpeed, m_maxAngleSpeed);
    m_currentAngle = std::max(
          0L, std::min(
          180L
        , deltaAngle + (long)m_currentAngle));

    m_servo->RotateTo(m_currentAngle);        
}