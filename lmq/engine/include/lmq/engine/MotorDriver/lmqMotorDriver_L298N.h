#pragma once

#include <stdint.h>

#include <Pair.h>

typedef Pair<uint8_t, uint8_t> lmqPowerRange;

#define lmq_DRIVER_L298N_MAX_POWER 255

class lmqMotorDriver_L298N
{
public:
    struct Channel
    {
        uint8_t input1Pin;
        uint8_t input2Pin;
        uint8_t enablePin;
    };

    enum EChannelFlag
    {
        CHANNELA = 1,
        CHANNELB = 2,
        ALL_CHANNELS = 3
    };

    enum EMode
    {
        STOP = 0,
        FORWARD = 1,
        BACKWARD = 2
    };

public:
    lmqMotorDriver_L298N(
          Channel channelA
        , Channel channelB);

    void Initialize();
    void SetPower(
          EChannelFlag channelMask
        , uint8_t power);
    void SetMode(
          EChannelFlag channelMask
        , EMode direction);
    void SetPowerLimits(
          EChannelFlag channelMask
        , lmqPowerRange powerLimit);

private:
    Channel m_channels[2];
    lmqPowerRange m_powerLimits[2];
};