#include "lmq/component/MotorDriver/lmqMotorDriver_L298N.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif // ARDUINO

inline void private_lmqMotorDriver_L298N_WriteModePins(
      lmqMotorDriver_L298N::Channel channel
    , lmqMotorDriver_L298N::EMode mode)
{
#ifdef ARDUINO
    switch(mode)
    {
    case lmqMotorDriver_L298N::EMode::STOP:
        digitalWrite(channel.input1Pin, LOW);
        digitalWrite(channel.input2Pin, LOW);
        break;
    case lmqMotorDriver_L298N::EMode::FORWARD:
        digitalWrite(channel.input1Pin, HIGH);
        digitalWrite(channel.input2Pin, LOW);
        break;
    case lmqMotorDriver_L298N::EMode::BACKWARD:
        digitalWrite(channel.input1Pin, LOW);
        digitalWrite(channel.input2Pin, HIGH);
        break;
    }
#endif // ARDUINO
}

lmqMotorDriver_L298N::lmqMotorDriver_L298N(
      Channel channelA
    , Channel channelB)
    : m_channels{ channelA, channelB }
    , m_powerLimits{ {0, 255}, {0, 255} }
{
    for(uint8_t i = 0; (1 << i) < EChannelFlag::ALL_CHANNELS; ++i)
    {
#ifdef ARDUINO
        pinMode(m_channels[i].input1Pin, OUTPUT);
        pinMode(m_channels[i].input2Pin, OUTPUT);
        pinMode(m_channels[i].enablePin, OUTPUT);
#endif // ARDUINO
    }
}

void lmqMotorDriver_L298N::SetPower(
      EChannelFlag channelMask
    , uint8_t power)
{
    for(uint8_t i = 0; (1 << i) < EChannelFlag::ALL_CHANNELS; ++i)
    {
        if((1 << i) & channelMask)
        {
#ifdef ARDUINO
            analogWrite(
                  m_channels[i].enablePin
                , power == 0
                    ? 0
                    : map(power, 1, 255, m_powerLimits[i].first(), m_powerLimits[i].second()));
#endif // ARDUINO
        }
    }
}

void lmqMotorDriver_L298N::SetMode(
      EChannelFlag channelMask
    , EMode mode)
{
    for(uint8_t i = 0; (1 << i) < EChannelFlag::ALL_CHANNELS; ++i)
    {
        if((1 << i) & channelMask)
        {
            private_lmqMotorDriver_L298N_WriteModePins(m_channels[i], mode);
        }
    }
}

void lmqMotorDriver_L298N::SetPowerLimits(
      EChannelFlag channelMask
    , lmqPowerRange powerLimit)
{
    for(uint8_t i = 0; (1 << i) < EChannelFlag::ALL_CHANNELS; ++i)
    {
        if((1 << i) & channelMask)
        {
            m_powerLimits[i] = powerLimit;
        }
    }  
}