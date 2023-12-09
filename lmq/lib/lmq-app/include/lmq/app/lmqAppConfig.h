
#define lmq_CORE_APP_UPDATE_PERIOD_MS 100

#define lmq_CONSOLE_BAUD 115200

#define lmq_GAMEPAD_STICK_THRESHOLD 50
#define lmq_GAMEPAD_TRIGGER_THRESHOLD 30

#define lmq_MD_L298N_POWER_LIMITS_6V_MOTOR_7_4V_PS lmqPowerRange(100, 230)
#define lmq_MD_L298N_POWER_LIMITS_6V_MOTOR_9V_PS lmqPowerRange(85, 150)
#define lmq_DEFAULT_MD_L298N_POWER_LIMITS lmq_MD_L298N_POWER_LIMITS_6V_MOTOR_7_4V_PS

#define lmq_MD_L298N_LEFT_CHANNEL_MASK lmqMotorDriver_L298N::CHANNELB

#define lmq_ROBOT_HEAD_SERVO_MOTOR_MAX_ANGLE_SPEED 7
#define lmq_ROBOT_HEAD_SERVO_MOTOR_INIT_ANGLE 90

#ifdef ESP32

#define lmq_MOTOR_DRIVER_L298N_ENA_PIN 27
#define lmq_MOTOR_DRIVER_L298N_IN1_PIN 12
#define lmq_MOTOR_DRIVER_L298N_IN2_PIN 14

#define lmq_MOTOR_DRIVER_L298N_ENB_PIN 33
#define lmq_MOTOR_DRIVER_L298N_IN3_PIN 26
#define lmq_MOTOR_DRIVER_L298N_IN4_PIN 25

#define lmq_ROBOT_HEAD_SERVO_MOTOR_PIN 13

#else // !ESP32
#error "The application is not configured for the platform"
#endif // ESP32