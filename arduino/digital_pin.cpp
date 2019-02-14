#include "digital_pin.h"

Led led_init(Led *led)
{
  pinMode(led->pin, OUTPUT);

  if (led->value != LED_OFF)
  {
    led_set_state(led);
    digitalWrite(led->pin, HIGH);
  }

  return *led;
}

bool led_get_state(Led *led)
{
  bool state;
  if (digitalRead(led->pin) == HIGH)
  {
    state = true;
  }
  else
  {
    state = false;
  }
  return state;
}

bool led_set_state(Led *led)
{
  if (led->action == LED_LIGHT) {
    digitalWrite(led->pin, HIGH);
  } else {
    digitalWrite(led->pin, LOW);
  }
}
