#ifndef DIGITAL_PIN_H_
#define DIGITAL_PIN_H_

#include "Arduino.h"
#include "digital_pin.h"

typedef enum LedPosition
{
  LED_FRONT,
  LED_PARKING,
} LedPosition;

typedef enum LedAction
{
  LED_LIGHT,
  LED_BLINK
} LedAction;

typedef enum LedValue
{
  LED_OFF,
  LED_SLOW,
  LED_NORMAL,
  LED_FAST
} LedValue;

typedef struct Led
{
  int pin;
  LedPosition position;
  LedAction action;
  LedValue value;
  int step_length;
  int estimate_steps;
  int max_steps;
} Led;

Led led_init(Led *led);
bool led_get_state(Led *led);
bool led_set_state(Led *led);

#endif /* DIGITAL_PIN_H_ */
