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

//In millisonds
const long TIMER_LENGTH = 15 * 1000;
const long RAINBOW_ANIMATION_SPEED_DELAY = 50;

long lastTimeWePressedTheButton = 0;

uint8_t hue = 0;
long lastTimeWeIncrementedHue = 0;

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

    fill(0, 255, 0);
    delay(3000);
    fill(0, 0, 0);
}

void loop()
{
    long ms = millis();

    if (digitalRead(PIN_BUTTON) == LOW)
    {
        lastTimeWePressedTheButton = (ms + TIMER_LENGTH);
    }

    if (ms > lastTimeWePressedTheButton)
    {
        fill(0, 0, 0);
    }
    else
    {

        rainbowAnimation();
    }
}

void rainbowAnimation()
{
    long ms = millis();
    if (ms > lastTimeWeIncrementedHue)
    {
        lastTimeWeIncrementedHue = (ms + RAINBOW_ANIMATION_SPEED_DELAY);
        fill_rainbow_fixed(leds, NUM_LEDS, hue, 10);
        FastLED.show();
        hue++;
        if (hue > 255)
        {
            hue = 0;
        }
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

//https://github.com/FastLED/FastLED/blob/11ed509736c6d88896f7680d1c4dfb9ff66667d9/colorutils.cpp
//Fixes an issue with a red pixel flickering
void fill_rainbow_fixed(struct CRGB *pFirstLED, int numToFill, uint8_t initialhue, uint8_t deltahue)
{
    CHSV hsv;
    hsv.hue = initialhue;
    hsv.val = 255;
    hsv.sat = 255;
    for (int i = 0; i < numToFill; i++)
    {
        pFirstLED[i] = hsv;
        hsv.hue += deltahue;
    }
}