#include "Arduino.h"
#include "digital_pin.h"

#define ON_BOARD_LED_PIN 13
#define END_OF_LINE '\n'
#define SERIAL_BODS 9600
#define SERIAL_TIMEOUT 8
#define LEDS_COUNT 1

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
 * MANAGE GROUP OF LEDS
 */
//
// 1011 0001
// bool led_exist(Led *leds[], String id)
// {
//   for (int i = 0; i < LEDS_COUNT; i++)
//   {
//     if (id.equals(leds[i]->id))
//     {
//       return true;
//     }
//   }
//   return false;
// }

Led* led_find(Led* leds[], int position)
{

    for (int i = 0; i < LEDS_COUNT; i++) {
        if (leds[i]->position == position) {
            return leds[i];
        }
    }
}

void led_handler(Led* led, int action, int value)
{
}
//

/*
 * MAIN BLOCK
 */
Led front_led = {
    ON_BOARD_LED_PIN,
    LED_FRONT,
    LED_LIGHT,
    LED_NORMAL,
    64,
    1024,
    1024
};

Led* leds[LEDS_COUNT] = {
    &front_led
};

int exclude_data(byte request, RequestData request_data)
{
    byte res = (request >> request_data) & 3;
    return (int)res;
}

void setup()
{
    pinMode(front_led.pin, OUTPUT);

    Serial.begin(SERIAL_BODS);
    Serial.setTimeout(SERIAL_TIMEOUT);

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // send startup config
    Serial.println("Goodnight moon!");
}


void loop()
{ // run over and over

    // LEDS
    for (int i = 0; i < LEDS_COUNT; i++) {

        if (leds[i]->value == LED_OFF) {
            digitalWrite(leds[i]->pin, LOW);
            continue;
        }

        switch (leds[i]->action) {
        case LED_LIGHT:
            digitalWrite(leds[i]->pin, HIGH);
            break;
        case LED_BLINK:
            leds[i]->estimate_steps -= leds[i]->value * leds[i]->value * leds[i]->step_length;
            if (leds[i]->estimate_steps <= 0) {
                digitalWrite(leds[i]->pin, !digitalRead(leds[i]->pin));
                leds[i]->estimate_steps = leds[i]->max_steps;
            }
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

        switch (detail) {
        case DETAIL_LED:
            Led* led = led_find(leds, position);
            led->action = (LedAction)action;
            led->value = (LedValue)value;
            break;
        }
    }

    delay(32);
}
