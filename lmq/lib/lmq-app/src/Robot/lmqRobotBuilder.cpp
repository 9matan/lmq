#include "lmq/app/lmqAppConfig.h"
#include "lmq/app/Robot/lmqRobotBuilder.h"

#include "lmq/robot/lmqRobot_Syrnyk.h"

static lmqRobot* BuildRobot_L298N();

lmqRobot* lmqBuildDefaultRobot()
{
    return BuildRobot_L298N();
}

static lmqRobot* BuildRobot_L298N()
{
    lmqMotorDriver_L298N::Channel channelA;
    channelA.enablePin = lmq_MOTOR_DRIVER_L298N_ENA_PIN;
    channelA.input1Pin = lmq_MOTOR_DRIVER_L298N_IN1_PIN;
    channelA.input2Pin = lmq_MOTOR_DRIVER_L298N_IN2_PIN;

    lmqMotorDriver_L298N::Channel channelB;
    channelB.enablePin = lmq_MOTOR_DRIVER_L298N_ENB_PIN;
    channelB.input1Pin = lmq_MOTOR_DRIVER_L298N_IN3_PIN;
    channelB.input2Pin = lmq_MOTOR_DRIVER_L298N_IN4_PIN;

    auto robot = new lmqRobot_Syrnyk(
          channelA
        , channelB
        , lmq_MD_L298N_LEFT_CHANNEL_MASK
        , lmq_ROBOT_HEAD_SERVO_MOTOR_PIN
        , lmq_ROBOT_HEAD_SERVO_MOTOR_MAX_ANGLE_SPEED
        , lmq_ROBOT_HEAD_SERVO_MOTOR_INIT_ANGLE);
    
    robot->SetMotorDriverPowerLimits(
        lmq_DEFAULT_MD_L298N_POWER_LIMITS);

    return robot;
}