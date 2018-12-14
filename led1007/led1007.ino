/* improved traveling theatre marquis effects  */

#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 74

// What pin are you using for data (in series with 470 ohm resistor)?
#define DATA_PIN 6
// #define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

/* Last time we had two sets up colors traveling in a theatre marquis.
   This time we will add anther offset variable to get better speed control
   over each color.
   Changing the offset to floats to get finer grained speed control effects
   Adding anoter offset variable.                                           */

void loop() {
  static float offset1;
  static float offset2;

  offset1 = offset1 + 0.25; // note that these are floats
  offset2 = offset2 - 0.6;  // we will need to cast them back to
  //                        // ints before using modulo operator

  FastLED.clear();  // set them all to black before beginning
  
  for (int i = 0; i < NUM_LEDS; i++) {

    if ((i + (int)offset1) % 16 == 0 ) {   // note cast back to int
      leds[i] = CRGB(100, 0, 150);
    }

    if ((i + (int)offset2) % 16 == 0 ) {  // note cast back to int
      leds[i] += CRGB(70, 170, 0);
    }
  }
  FastLED.show();
  delay(20);    // controls the speed
}


