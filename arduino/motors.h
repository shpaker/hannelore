#ifndef MOTORS_H_
#define MOTORS_H_

typedef enum MotorPosition {
    MOTOR_STEERING,
    MOTOR_ACCELERATION
} MotorPosition;

typedef enum MotorAction {
    MOTOR_FORWARD,
    MOTOR_BACKWARD
} MotorAction;

typedef enum MotorValue {
    MOTOR_OFF,
    MOTOR_SLOW,
    MOTOR_NORMAL,
    MOTOR_FAST
} MotorValue;

typedef struct Motor {
    int pwm_pin;
    int out1_pin;
    int out2_pin;
    MotorPosition position;
    MotorAction action;
    MotorValue value;
} Motor;

Motor motors[MOTORS_COUNT] = {
    Motor{
        // STEERING WHEEL
        STEERING_PWM_MOTOR_PIN, // pwm_pin
        STEERING_OUT1_MOTOR_PIN, // out1_pin
        STEERING_OUT2_MOTOR_PIN, // out2_pin
        MOTOR_STEERING, // position
        MOTOR_FORWARD, // action
        MOTOR_OFF // value
    },
    Motor{
        // ACCELERATOR
        ACCELERATION_PWM_MOTOR_PIN, // pwm_pin
        ACCELERATION_OUT1_MOTOR_PIN, // out1_pin
        ACCELERATION_OUT2_MOTOR_PIN, // out2_pin
        MOTOR_ACCELERATION, // position
        MOTOR_FORWARD, // action
        MOTOR_OFF // value
    }
};

#endif /* MOTORS_H_ */
