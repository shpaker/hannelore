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

Led led_find(Led* leds[], int position)
{

    for (int i = 0; i < LEDS_COUNT; i++) {
        if (leds[i]->position == position) {
            return *leds[i];
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
    LED_OFF
};

Led* leds[LEDS_COUNT] = {
    &front_led
};

void setup()
{
    led_init(&front_led);
    Serial.begin(SERIAL_BODS);
    Serial.setTimeout(SERIAL_TIMEOUT);

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // send startup config
    Serial.println("Goodnight moon!");
}

int exclude_data(byte request, RequestData request_data)
{
    byte res = (request >> request_data) & 3;
    return (int)res;
}

void loop()
{ // run over and over

    if (Serial.available()) {

        // recieve package

        // for (int i=0) {}

        // recieve one line
        byte recieved = Serial.read();

        int detail = exclude_data(recieved, REQUEST_DETAIL);
        int position = exclude_data(recieved, REQUEST_POSITION);
        int action = exclude_data(recieved, REQUEST_ACTION);
        int value = exclude_data(recieved, REQUEST_VALUE);

        Led a;
        switch (detail) {
        case DETAIL_LED:
            a = led_find(leds, position);
            break;
        case DETAIL_MOTOR:
            break;
        }

        switch (action) {
        case LED_LIGHT:
            Serial.println("LED_LIGHT");
            a.action = LED_LIGHT;
            led_set_state(&a);
            break;
        case LED_BLINK:
            Serial.println("LED_BLINK");
            a.action = LED_BLINK;
            led_set_state(&a);
            break;
        }

        // Led led;

        // if (recieved == "1")
        // {
        //   if (led_exist(leds, String("front_led_1")))
        //   {
        //     led = led_find(leds, String("front_led_1"));
        //     led_set_state(&led, true);
        //   }
        // }
        // else
        // {
        //   led = led_find(leds, String("front_led_1"));
        //   led_set_state(&led, false);
        // }
        // Serial.write(recieved);ß
        // Serial.write(recieved);

        // if (led_get_state(&front_led))
        // {
        //   Serial.println("ON");
        // }
        // else
        // {
        //   Serial.println("OFF");
        // }
    }

    delay(100);
}
