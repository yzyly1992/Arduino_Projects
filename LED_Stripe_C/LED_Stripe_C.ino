#include "FastLED.h"
#define NUM_LEDS 80
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
int chosenSlots[NUM_LEDS + 1];
const uint8_t kMatrixWidth  = 16;
const uint8_t kMatrixHeight = 5;
const bool    kMatrixSerpentineLayout = false;
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
static uint16_t x;
static uint16_t y;
static uint16_t z;
uint16_t speed = 1;
uint16_t scale = 16;
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

CRGBPalette16 currentPalette( PartyColors_p );
uint8_t       colorLoop = 1;

int eightOrder[] = {0, 1, 2, 16, 18, 32, 33, 34, 48, 50, 64, 65, 66};
int eightMaxIndex = sizeof(eightOrder) / sizeof(eightOrder[0]);
int oneOrder[] = {0, 1, 2, 17, 33, 49, 64, 65};
int oneMaxIndex = sizeof(oneOrder) / sizeof(oneOrder[0]);
int twoOrder[] = {0, 1, 2, 16, 32, 33, 34, 50, 66, 65, 64};
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

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

CHSV colorP[] = {CHSV(0, 150, 100), CHSV(20, 255, 15), CHSV(50, 150, 50), CHSV(120, 150, 50), CHSV(140, 200, 50),
                 CHSV(200, 150, 50), CHSV(220, 150, 50)
                }; // add as many as you like - nothing should break!
// color palette not used in this demo!

int maxIndex = sizeof(colorP) / sizeof(colorP[0]);

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(4, INPUT);
  fillUpArray();
  x = random16();
  y = random16();
  z = random16();
  SetupRandomPalette();
}



void fillUpArray() {
  for (int i = 0; i < 74; i++) {
    chosenSlots[i] = i; // fill up the array with index numbers
  }
}

void fillnoise8() {
  // If we're runing at a low "speed", some 8-bit artifacts become visible
  // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  // The amount of data smoothing we're doing depends on "speed".
  uint8_t dataSmoothing = 1;
  if ( speed < 50) {
    dataSmoothing = 200 - (speed * 4);
  }

  for (int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for (int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;

      uint8_t data = inoise8(x + ioffset, y + joffset, z);

      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      data = qsub8(data, 16);
      data = qadd8(data, scale8(data, 39));

      if ( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }

      noise[i][j] = data;
    }
  }

  z += speed;

  // apply slow drift to X and Y, just for visual variation.
  x += speed / 16;
  y -= speed / 32;
}

void mapNoiseToLEDsUsingPalette()
{
  static uint8_t ihue = 0;

  for (int i = 0; i < kMatrixWidth; i++) {
    for (int j = 0; j < kMatrixHeight; j++) {
      // We use the value at the (i,j) coordinate in the noise
      // array for our brightness, and the flipped value from (j,i)
      // for our pixel's index into the color palette.

      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];

      // if this palette is a 'loop', add a slowly-changing base value
      if ( colorLoop) {
        index += ihue;
      }

      // brighten up, as the color palette itself often contains the
      // light/dark dynamic range desired
      if ( bri > 127 ) {
        bri = 255;
      } else {
        bri = dim8_raw( bri * 2);
      }

      CRGB color = ColorFromPalette( currentPalette, index, bri);
      leds[XY(i, j)] = color;
    }
  }

  ihue += 1;
}

void loop() {

  buttonState = digitalRead(4);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      if (buttonPushCounter > 5) {
        buttonPushCounter = 0;
      }
    }
  } else {

    if (buttonPushCounter == 2) {

      static float offset1;
      static float offset2;

      offset1 = offset1 + 0.05; // note that these are floats

      FastLED.clear();  // set them all to black before beginning

      for (int i = 0; i < 74; i++) {

        if ((i + (int)offset1) % 16 == 0 ) {   // note cast back to int
          leds[i] = CRGB(70, 170, 0);
        }

        if ((i + (int)offset1) % 16 == 2 ) {  // note cast back to int
          leds[i] += CRGB(100, 0, 150);
        }

        if ((i + (int)offset1) % 16 == 4 ) {  // note cast back to int
          leds[i] += CRGB(70, 170, 0);
        }

        if ((i + (int)offset1) % 16 == 5 ) {  // note cast back to int
          leds[i] += CRGB(70, 170, 0);
        }

        if ((i + (int)offset1) % 16 == 6 ) {  // note cast back to int
          leds[i] += CRGB(70, 170, 0);
        }

        if ((i + (int)offset1) % 16 == 8 ) {  // note cast back to int
          leds[i] += CRGB(100, 0, 150);
        }

        if ((i + (int)offset1) % 16 == 10 ) {  // note cast back to int
          leds[i] += CRGB(100, 0, 150);
        }

        if ((i + (int)offset1) % 16 == 12 ) {  // note cast back to int
          leds[i] += CRGB(70, 170, 0);
        }

        if ((i + (int)offset1) % 16 == 13 ) {  // note cast back to int
          leds[i] += CRGB(70, 170, 0);
        }

        if ((i + (int)offset1) % 16 == 15 ) {  // note cast back to int
          leds[i] += CRGB(70, 170, 0);
        }
      }
    }

    if (buttonPushCounter == 1) {

      static float offset3;
      static float offset4;

      offset3 = offset3 + 0.25; // note that these are floats
      offset4 = offset4 - 0.6;  // we will need to cast them back to
      //                        // ints before using modulo operator

      FastLED.clear();  // set them all to black before beginning

      for (int i = 0; i < 74; i++) {

        if ((i + (int)offset3) % 16 == 0 ) {   // note cast back to int
          leds[i] = CRGB(100, 0, 150);
        }

        if ((i + (int)offset4) % 16 == 0 ) {  // note cast back to int
          leds[i] += CRGB(70, 170, 0);
        }
      }
    }

    if (buttonPushCounter == 3) {
      static float offset5;

      offset5 = offset5 + 0.25; // note that these are floats


      if (offset5 > 13) {
        offset5 = 0;
        countN = countN + 1;
        if (countN > 9) {
          countN = 0;
        }
      }


      FastLED.clear();

      if (countN == 0) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < oneMaxIndex; l++) {
            int k = oneOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(20, 50, 255);
            }
          }
        }
      }

      if (countN == 1) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < twoMaxIndex; l++) {
            int k = twoOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(50, 100, 200);
            }
          }
        }
      }

      if (countN == 2) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < threeMaxIndex; l++) {
            int k = threeOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(70, 150, 150);
            }
          }
        }
      }

      if (countN == 3) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < fourMaxIndex; l++) {
            int k = fourOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(50, 150, 50);
            }
          }
        }
      }

      if (countN == 4) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < fiveMaxIndex; l++) {
            int k = fiveOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(100, 200, 20);
            }
          }
        }
      }

      if (countN == 5) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < sixMaxIndex; l++) {
            int k = sixOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(150, 255, 20);
            }
          }
        }
      }

      if (countN == 6) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < sevenMaxIndex; l++) {
            int k = sevenOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(150, 100, 20);
            }
          }
        }
      }

      if (countN == 7) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < eightMaxIndex; l++) {
            int k = eightOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(200, 100, 20);
            }
          }
        }
      }

      if (countN == 8) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < nineMaxIndex; l++) {
            int k = nineOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(255, 120, 50);
            }
          }
        }
      }

      if (countN == 9) {
        for (int i = 0; i <= 74; i++) {
          for (int l = 0; l < zeroMaxIndex; l++) {
            int k = zeroOrder[l];
            if ((i - (int)offset5) % 74 == k ) {   // note cast back to int
              leds[i] = CRGB(255, 150, 150);
            }
          }
        }
      }
    }
  }

  if (buttonPushCounter == 4) {
    static int pixIndex = NUM_LEDS;   // index for pixels
    static int arrayIndex = 0; // index for the color array
    static CHSV color = CHSV(0, 200, 150);

    int randNo = random(pixIndex); // choose a random pixel from array
    int randPix = chosenSlots[randNo]; // get its value

    leds[randPix] = color;
    color.hue = color.hue + (random(17) - 8); // random walk
    color.sat = color.sat + (random(7) - 3); // random walk
    color.value = color.value + (random(11) - 5);
    FastLED.show();
    delay(1);

    --pixIndex;
    chosenSlots[randNo] = chosenSlots[pixIndex];

    if (pixIndex == 0) {    // if all done - start over
      fillUpArray();        // reset array
      pixIndex = NUM_LEDS;  // reset pixIndex
      FastLED.show();
    }
  }

  if (buttonPushCounter == 5) {
    ChangePaletteAndSettingsPeriodically();
    fillnoise8();
    mapNoiseToLEDsUsingPalette();
  }



  FastLED.show();
  delay(15);
  // controls the speed

  lastButtonState = buttonState;
}

#define HOLD_PALETTES_X_TIMES_AS_LONG 1

void ChangePaletteAndSettingsPeriodically()
{
  return;

  uint8_t secondHand = ((millis() / 1000) / HOLD_PALETTES_X_TIMES_AS_LONG) % 60;
  static uint8_t lastSecond = 99;

  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand ==  0)  {
      currentPalette = RainbowColors_p;
      speed = 20;
      scale = 30;
      colorLoop = 1;
    }
    if ( secondHand ==  5)  {
      SetupPurpleAndGreenPalette();
      speed = 10;
      scale = 50;
      colorLoop = 1;
    }
    if ( secondHand == 10)  {
      SetupBlackAndWhiteStripedPalette();
      speed = 20;
      scale = 30;
      colorLoop = 1;
    }
    if ( secondHand == 15)  {
      currentPalette = ForestColors_p;
      speed =  8;
      scale = 120;
      colorLoop = 0;
    }
    if ( secondHand == 20)  {
      currentPalette = CloudColors_p;
      speed =  4;
      scale = 30;
      colorLoop = 0;
    }
    if ( secondHand == 25)  {
      currentPalette = LavaColors_p;
      speed =  8;
      scale = 50;
      colorLoop = 0;
    }
    if ( secondHand == 30)  {
      currentPalette = OceanColors_p;
      speed = 20;
      scale = 90;
      colorLoop = 0;
    }
    if ( secondHand == 35)  {
      currentPalette = PartyColors_p;
      speed = 20;
      scale = 30;
      colorLoop = 1;
    }
    if ( secondHand == 40)  {
      SetupRandomPalette();
      speed = 20;
      scale = 20;
      colorLoop = 1;
    }
    if ( secondHand == 45)  {
      SetupRandomPalette();
      speed = 50;
      scale = 50;
      colorLoop = 1;
    }
    if ( secondHand == 50)  {
      SetupRandomPalette();
      speed = 90;
      scale = 90;
      colorLoop = 1;
    }
    if ( secondHand == 55)  {
      currentPalette = RainbowStripeColors_p;
      speed = 30;
      scale = 20;
      colorLoop = 1;
    }
  }
}

// This function generates a random palette that's a gradient
// between four different colors.  The first is a dim hue, the second is
// a bright hue, the third is a bright pastel, and the last is
// another bright hue.  This gives some visual bright/dark variation
// which is more interesting than just a gradient of different hues.
void SetupRandomPalette()
{
  currentPalette = CRGBPalette16(
                     CHSV( random8(), 200, 32),
                     CHSV( random8(), 255, 180),
                     CHSV( random8(), 128, 255),
                     CHSV( random8(), 50, 150),
                     CHSV( random8(), 200, 32),
                     CHSV( random8(), 255, 180),
                     CHSV( random8(), 128, 255),
                     CHSV( random8(), 50, 150),
                     CHSV( random8(), 200, 32),
                     CHSV( random8(), 255, 180),
                     CHSV( random8(), 128, 255),
                     CHSV( random8(), 50, 150),
                     CHSV( random8(), 200, 32),
                     CHSV( random8(), 255, 180),
                     CHSV( random8(), 128, 255),
                     CHSV( random8(), 50, 150));
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     green,  green,  black,  black,
                     purple, purple, black,  black,
                     green,  green,  black,  black,
                     purple, purple, black,  black );
}


//
// Mark's xy coordinate mapping code.  See the XYMatrix for more information on it.
//
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  if ( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }
  if ( kMatrixSerpentineLayout == true) {
    if ( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  return i;
}


