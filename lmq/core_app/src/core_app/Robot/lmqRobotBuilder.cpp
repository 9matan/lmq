#include "lmq/core_app/lmqCoreAppConfig.h"

#include "lmq/core_app/Robot/lmqRobotBuilder.h"

#include "lmq/core_app/Robot/lmqRobot_L298N.h"

static lmqRobot* BuildRobot_L298N();

lmqRobot* lmqBuildDefaultRobot()
{
    return BuildRobot_L298N();
}

static lmqRobot* BuildRobot_L298N()
{
    lmqMotorDriver_L298N::Channel channelA;
    channelA.enablePin = lmq_MOTOR_DRIVER_L298N_ENA;
    channelA.input1Pin = lmq_MOTOR_DRIVER_L298N_IN1;
    channelA.input2Pin = lmq_MOTOR_DRIVER_L298N_IN2;

    lmqMotorDriver_L298N::Channel channelB;
    channelB.enablePin = lmq_MOTOR_DRIVER_L298N_ENB;
    channelB.input1Pin = lmq_MOTOR_DRIVER_L298N_IN3;
    channelB.input2Pin = lmq_MOTOR_DRIVER_L298N_IN4;

    auto robot = new lmqRobot_L298N(
          channelA
        , channelB
        , lmq_MD_L298N_LEFT_CHANNEL_MASK);
    
    robot->Initialize();
    robot->SetMotorDriverPowerLimits(
        lmq_DEFAULT_MD_L298N_POWER_LIMITS);

    return robot;
}