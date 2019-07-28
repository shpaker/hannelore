#include "Arduino.h"

#include "config.h"
#include "leds.h"
#include "motors.h"

#define EXCLUDE_BITS(request, bits_offset) (request >> bits_offset & 0x3)

byte acceleration_speeds[] = {
    0x0,
    0x60,
    0x80,
    0xFF
};

byte steering_speeds[] = {
    0x0,
    0x8E,
    0xA0,
    0xFF
};

typedef enum Detail {
    DETAIL_LED,
    DETAIL_MOTOR
} Detail;

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
        Motor* motor = &motors[i];

        byte speed;

        if (motor->position == MOTOR_ACCELERATION) {
            speed = acceleration_speeds[motor->value];
        } else {
            speed = steering_speeds[motor->value];
        }

        analogWrite(motor->pwm_pin, speed);

        switch (motor->action) {
        case MOTOR_FORWARD:
            digitalWrite(motor->out1_pin, HIGH);
            digitalWrite(motor->out2_pin, LOW);
            break;
        case MOTOR_BACKWARD:
            digitalWrite(motor->out1_pin, LOW);
            digitalWrite(motor->out2_pin, HIGH);
            break;
        }
    }

    // UART
    if (Serial.available()) {

        byte recieved = Serial.read();

        byte detail = EXCLUDE_BITS(recieved, BIT_DETAIL);
        byte position = EXCLUDE_BITS(recieved, BIT_POSITION);
        byte action = EXCLUDE_BITS(recieved, BIT_ACTION);
        byte value = EXCLUDE_BITS(recieved, BIT_VALUE);

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
