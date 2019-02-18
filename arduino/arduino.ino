#include "Arduino.h"
#include "digital_pin.h"

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

// USART OPTIONS
#define SERIAL_BODS 19200
#define SERIAL_TIMEOUT 8

#define LEDS_COUNT 2
#define MOTORS_COUNT 2

typedef enum Detail {
    DETAIL_LED,
    DETAIL_MOTOR
} Detail;

typedef enum RequestData {
    REQUEST_DETAIL = 6,
    REQUEST_POSITION = 4,
    REQUEST_ACTION = 2,
    REQUEST_VALUE = 0
} RequestData;

/*
 * MAIN BLOCK
 */

// Led* leds[LEDS_COUNT] = { &front_leds, &parking_leds };
// Motor* motors[MOTORS_COUNT] = { &acceleration_motor, &steering_motor };

Led leds[LEDS_COUNT] = {
    Led{
        // FRONTAL LIGHTS
        FRONT_LEDS_PIN, // pin
        LED_FRONT, // position
        LED_LIGHT, // action
        LED_OFF, // value
        64, // blinking: step_length
        1024, // blinking: estimate_steps
        1024 // blinking: max_steps
    },
    Led{
        // PARKING LIGHTS
        PARKING_LEDS_PIN, // pin
        LED_PARKING, // position
        LED_LIGHT, // action
        LED_OFF, // value
        64, // blinking: step_length
        1024, // blinking: estimate_steps
        1024 // blinking: max_steps
    }
};

Motor motors[MOTORS_COUNT] = {
    Motor{
        // STEERING WHEEL
        STEERING_PWM_MOTOR_PIN, // pwm_pin
        STEERING_OUT1_MOTOR_PIN, // out1_pin
        STEERING_OUT2_MOTOR_PIN, // out2_pin
        MOTOR_ACCELERATION, // position
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

int exclude_data(byte request, RequestData request_data)
{
    byte res = (request >> request_data) & 3;
    return (int)res;
}

void setup()
{

    for (int i = 0; i < LEDS_COUNT; i++) {
        pinMode(leds[i].pin, OUTPUT);
    }

    for (int i = 0; i < MOTORS_COUNT; i++) {
        pinMode(motors[i].pwm_pin, OUTPUT);
        pinMode(motors[i].out1_pin, OUTPUT);
        pinMode(motors[i].out2_pin, OUTPUT);
    }

    Serial.begin(SERIAL_BODS);
    Serial.setTimeout(SERIAL_TIMEOUT);

    while (!Serial) {
        ; // wait for serial port to connect
    }
}

void loop()
{

    // LEDS
    for (int i = 0; i < LEDS_COUNT; i++) {
        Led* led = &leds[i];

        if (led->value == LED_OFF) {
            digitalWrite(led->pin, LOW);
            continue;
        }

        switch (led->action) {
        case LED_LIGHT:
            digitalWrite(led->pin, HIGH);
            break;
        case LED_BLINK:
            led->estimate_steps -= led->value * led->value * led->step_length;
            if (led->estimate_steps <= 0) {
                digitalWrite(led->pin, !digitalRead(led->pin));
                led->estimate_steps = led->max_steps;
            }
            break;
        }
    }

    // MOTORS
    for (int i = 0; i < MOTORS_COUNT; i++) {
        // Motor* motor = motors[i];

        byte speed = 255 / MOTOR_FAST * motors[i].value;
        // включаем мотор на максимальной скорости
        analogWrite(motors[i].pwm_pin, speed);

        switch (motors[i].action) {
        case MOTOR_FORWARD:
            digitalWrite(motors[i].out1_pin, HIGH);
            digitalWrite(motors[i].out2_pin, LOW);
            break;
        case MOTOR_BACKWARD:
            digitalWrite(motors[i].out1_pin, LOW);
            digitalWrite(motors[i].out2_pin, HIGH);
            break;
        }
    }

    // UART
    if (Serial.available()) {

        byte recieved = Serial.read();

        int detail = exclude_data(recieved, REQUEST_DETAIL);
        int position = exclude_data(recieved, REQUEST_POSITION);
        int action = exclude_data(recieved, REQUEST_ACTION);
        int value = exclude_data(recieved, REQUEST_VALUE);

        switch ((Detail)detail) {
        case DETAIL_LED: {
            leds[position].action = (LedAction)action;
            leds[position].value = (LedValue)value;
        } break;
        case DETAIL_MOTOR: {
            motors[position].action = (MotorAction)action;
            motors[position].value = (MotorValue)value;
        } break;
        }
    }

    delay(32);
}
