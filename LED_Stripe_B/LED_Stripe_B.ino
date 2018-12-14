
#include "FastLED.h"
#define NUM_LEDS 74
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
int chosenSlots[NUM_LEDS + 1];
CRGB colorP[] = {CRGB(0, 0, 255), CRGB(255, 0, 0), CRGB(0, 255, 0)
                };
int maxIndex = sizeof(colorP) / sizeof(colorP[0]);

          
void fillUpArray() {
  for (int i = 0; i < NUM_LEDS; i++) {
    chosenSlots[i] = i; // fill up the array with index numbers
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // put your setup code here, to run once:
  fillUpArray();

}

void loop() {
  // put your main code here, to run repeatedly:
  static int pixIndex = NUM_LEDS;
  static int arrayIndex = 0; // index for the color array
  static CRGB color = CRGB(255, 0, 0);

  color.red = color.red 
  
  int randNo = random(pixIndex); // choose a random pixel from array
  int randPix = chosenSlots[randNo]; // get its value

  leds[randPix] = color;
  
}
