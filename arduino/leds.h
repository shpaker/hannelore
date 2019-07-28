#ifndef LEDS_H_
#define LEDS_H_

typedef enum LedPosition {
    LED_FRONT,
    LED_PARKING,
} LedPosition;

typedef enum LedAction {
    LED_LIGHT,
    LED_BLINK
} LedAction;

typedef enum LedValue {
    LED_OFF,
    LED_SLOW,
    LED_NORMAL,
    LED_FAST
} LedValue;

typedef struct Led {
    int pin;
    LedPosition position;
    LedAction action;
    LedValue value;
    int step_length;
    int estimate_steps;
    int max_steps;
} Led;

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

#endif /* LEDS_H_ */
