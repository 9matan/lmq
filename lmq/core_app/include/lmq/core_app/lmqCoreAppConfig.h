
#define lmq_MD_L298N_POWER_LIMITS_6V_MOTOR_7_4V_PS lmqPowerRange(100, 230/*175*/)
#define lmq_MD_L298N_POWER_LIMITS_6V_MOTOR_9V_PS lmqPowerRange(85, 150)
#define lmq_DEFAULT_MD_L298N_POWER_LIMITS lmq_MD_L298N_POWER_LIMITS_6V_MOTOR_7_4V_PS

#define lmq_CONSOLE_BAUD 115200

#define lmq_GAMEPAD_STICK_THRESHOLD 15
#define lmq_GAMEPAD_TRIGGER_THRESHOLD 15

#ifdef ARDUINO_AVR_UNO

#define lmq_MOTOR_DRIVER_L298N_ENA 11
#define lmq_MOTOR_DRIVER_L298N_IN1 12
#define lmq_MOTOR_DRIVER_L298N_IN2 13

#define lmq_MOTOR_DRIVER_L298N_ENB 6
#define lmq_MOTOR_DRIVER_L298N_IN3 7
#define lmq_MOTOR_DRIVER_L298N_IN4 8

#elif defined(ESP32) // ARDUINO_AVR_UNO

#define lmq_MOTOR_DRIVER_L298N_ENA 27
#define lmq_MOTOR_DRIVER_L298N_IN1 12
#define lmq_MOTOR_DRIVER_L298N_IN2 14

#define lmq_MOTOR_DRIVER_L298N_ENB 33
#define lmq_MOTOR_DRIVER_L298N_IN3 26
#define lmq_MOTOR_DRIVER_L298N_IN4 25

#endif // ESP32