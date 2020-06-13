////////////////////////////////
///////NEW BOOT LOADER/////////
//////////////////////////////

#include <FastLED.h>

//4 strips of 7
#define NUM_LEDS 28
#define STRIP_LENGTH 7

//PIN for the leds
#define PIN_STRIP 10
#define PIN_BUTTON 9

//Define LEDS
CRGB leds[NUM_LEDS];

//type of LED
#define STRIP_TYPE WS2812
#define STRIP_COLOR_ORDER GRB

void setup()
{
    //register LEDS
    LEDS.addLeds<STRIP_TYPE, PIN_STRIP, STRIP_COLOR_ORDER>(leds, NUM_LEDS);

    //set brightness
    FastLED.setBrightness(63);

    //LOW means its being pressed
    pinMode(PIN_BUTTON, INPUT_PULLUP);

    //Random seed
    randomSeed(analogRead(0));
}

void loop()
{
    if (digitalRead(PIN_BUTTON) == LOW)
    {
        fill(0, 255, 0);
    }
    else
    {
        rainbowTest();
    }
}

uint8_t hue = 0;
void rainbowTest()
{
    fill_rainbow(leds, NUM_LEDS, hue, 10);
    FastLED.show();

    hue++;

    if (hue > 255)
    {
        hue = 0;
    }
}

void fill(uint8_t r, uint8_t g, uint8_t b)
{
    fill(r, g, b, 0, NUM_LEDS);
}

void fill(uint8_t r, uint8_t g, uint8_t b, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        leds[i] = CRGB(r, g, b);
    }
    FastLED.show();
}
