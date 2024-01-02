#pragma once

#define lmq_PS4_KEY_CODE_BEGIN 0
#define lmq_PS4_AXIS_CODE_BEGIN 0

enum class lmqPS4KeyCode
{
    Cross = lmq_PS4_KEY_CODE_BEGIN,
    Circle,
    Triangle,
    Square,

    Up,
    Down,
    Left,
    Right,

    End
};

enum class lmqPS4AxisCode
{
    LeftStickX = lmq_PS4_AXIS_CODE_BEGIN,
    LeftStickY,
    RightStickX,
    RightStickY,
    L2,
    R2,

    End
};