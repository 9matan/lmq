#pragma once

#include <stdint.h>

struct lmqGamepadControlsState;
class lmqRobotController;

class lmqGamepadInputController
{
public:
    lmqGamepadInputController(lmqRobotController* robotController);

    void OnGamepadControlsState(
        const lmqGamepadControlsState& gamepadControlsState);

    void SetStickThreshold(const uint8_t stickThreshold);
    void SetTriggerThreshold(const uint8_t triggerThreshold);

private:
    enum EMovementMode
    {
        AUTO_MOVEMENT_MODE = 0,
        MANUAL_MOVEMENT_MODE
    };

private:
    lmqRobotController* m_robotController;
    uint8_t m_stickThreshold;
    uint8_t m_triggerThreshold;
    EMovementMode m_movementMode;

private:
    void UpdateAutoMovementMode(const lmqGamepadControlsState& gamepadControlsState);
    void UpdateManualMovementMode(const lmqGamepadControlsState& gamepadControlsState);

    int8_t GetValueFromStick(
          const int8_t stickInput
        , const int8_t outMin
        , const int8_t outMax) const;
    
    int8_t GetValueFromTrigger(
          const uint8_t triggerInput
        , const int8_t outMin
        , const int8_t outMax) const;
};