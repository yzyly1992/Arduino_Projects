#include "FastLED.h"
#define NUM_LEDS 74
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
int eightOrder[] = {0, 1, 2, 16, 18, 32, 33, 34, 48, 50, 64, 65, 66};
int eightMaxIndex = sizeof(eightOrder) / sizeof(eightOrder[0]);
int oneOrder[] = {0,1,2,17,33,49,64,65};
int oneMaxIndex = sizeof(oneOrder) / sizeof(oneOrder[0]);
int twoOrder[] = {0,1,2,16,32,33,34,50,66,65,64};
int twoMaxIndex = sizeof(twoOrder) / sizeof(twoOrder[0]);
int threeOrder[] = {0, 1, 2, 18, 32, 33, 34, 50, 64, 65, 66};
int threeMaxIndex = sizeof(threeOrder) / sizeof(threeOrder[0]);
int fourOrder[] = {2, 18, 32, 33, 34, 48, 50, 64, 66};
int fourMaxIndex = sizeof(fourOrder) / sizeof(fourOrder[0]);
int fiveOrder[] = {0, 1, 2, 18, 32, 33, 34, 48, 64, 65, 66};
int fiveMaxIndex = sizeof(fiveOrder) / sizeof(fiveOrder[0]);
int sixOrder[] = {0, 1, 2, 16, 18, 32, 33, 34, 48, 64, 65, 66};
int sixMaxIndex = sizeof(sixOrder) / sizeof(sixOrder[0]);
int sevenOrder[] = {2, 18, 34, 50, 64, 65, 66};
int sevenMaxIndex = sizeof(sevenOrder) / sizeof(sevenOrder[0]);
int nineOrder[] = {0, 1, 2, 18, 32, 33, 34, 48, 50, 64, 65, 66};
int nineMaxIndex = sizeof(nineOrder) / sizeof(nineOrder[0]);
int zeroOrder[] = {0, 1, 2, 16, 18, 32, 34, 48, 50, 64, 65, 66};
int zeroMaxIndex = sizeof(zeroOrder) / sizeof(zeroOrder[0]);

int countN;


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:
  static float offset5;

  offset5 = offset5 + 0.25; // note that these are floats

  
  if (offset5 > 13) {
    offset5 = 0;
    countN = countN + 1;
    if (countN > 9){
      countN = 0;
    }
  }

  
  FastLED.clear();
  
  if (countN == 0){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < oneMaxIndex; l++) {
      int k = oneOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(20, 50, 255);
      }
    }
  }
  }

  if (countN == 1){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < twoMaxIndex; l++) {
      int k = twoOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(50, 100, 200);
      }
    }
  }
  }

  if (countN == 2){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < threeMaxIndex; l++) {
      int k = threeOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(70, 150, 150);
      }
    }
  }
  }

  if (countN == 3){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < fourMaxIndex; l++) {
      int k = fourOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(50, 150, 50);
      }
    }
  }
  }

  if (countN == 4){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < fiveMaxIndex; l++) {
      int k = fiveOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(100, 200, 20);
      }
    }
  }
  }

  if (countN == 5){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < sixMaxIndex; l++) {
      int k = sixOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(150, 255, 20);
      }
    }
  }
  }

  if (countN == 6){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < sevenMaxIndex; l++) {
      int k = sevenOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(150, 100, 20);
      }
    }
  }
  }

  if (countN == 7){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < eightMaxIndex; l++) {
      int k = eightOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(200, 100, 20);
      }
    }
  }
  }

  if (countN == 8){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < nineMaxIndex; l++) {
      int k = nineOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(255, 120, 50);
      }
    }
  }
  }

  if (countN == 9){
  for (int i = 0; i <= 74; i++) {
    for (int l = 0; l < zeroMaxIndex; l++) {
      int k = zeroOrder[l];
      if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
        leds[i] = CRGB(255, 150, 150);
      }
    }
  }
  }
    
  FastLED.show();
  delay(20);
}

