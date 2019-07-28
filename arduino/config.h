#ifndef CONFIG_H_
#define CONFIG_H_

// lights
#define FRONT_LEDS_PIN 3
#define PARKING_LEDS_PIN 4

// motors
#define ACCELERATION_OUT1_MOTOR_PIN 6
#define ACCELERATION_OUT2_MOTOR_PIN 7
#define ACCELERATION_PWM_MOTOR_PIN 5
#define STEERING_OUT1_MOTOR_PIN 8
#define STEERING_OUT2_MOTOR_PIN 9
#define STEERING_PWM_MOTOR_PIN 10

// USART options
#define SERIAL_BODS 19200
#define SERIAL_TIMEOUT 4

// array lengths
#define LEDS_COUNT 2
#define MOTORS_COUNT 2

// protocol bits
#define BIT_DETAIL 6
#define BIT_POSITION 4
#define BIT_ACTION 2
#define BIT_VALUE 0

#define MINIMAL_SPEED 0x2
#endif /* CONFIG_H_ */
