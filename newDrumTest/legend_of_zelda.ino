/*Example for the MusicWithoutDelay Library by Nathan Ramanathan. nathan6ramanathan@gmail.com
   This sketch puts all the functions to the test.

*/
//To learn more about this project go to https://github.com/nathanRamaNoodles/MusicWithoutDelay-LIbrary
#include <MusicWithoutDelay.h>
#include <Button.h>  //https://github.com/JChristensen/Button  acquired by JChristensen's popular button library
#include <Tone.h>                //https://github.com/bhagman/Tone
char *Soprano  = "Zelda:o=5,b=160,f=aeb:4b,4f+8.f,16b,16b,16c1,16d1,16e1,2f1,8p,8f1,12f1,12g_1,12a1,2b1,12p,12b1,12b1,12b1,12a1,12g_1,8.a1,16g_1,2f1,4f1,8e1,16e1,16f1,2g_1,8f1,8e1,8d_1,16d_1,16e1,2f1,8e1,8d_1,8c1,16c1,16d1,2e#1,4g1,8f1,16f,16f,8f,16f,16f,8f,16f,16f,8f,8f";
char *Bass     = ":b=160,f=aeb:4d,12d,12d,12c,8.d,16d,16d,16e,16f,16g,8.a,16b,16b,16c1,16d1,16e1,4f1,12a,12b,12c1,8.d_1,16g_,16g_,16a,16b,16c1,12d_1,12p,12d_1,12d_1,12c1,12b,8.d_,16a,12a,12a,12g_,8.a,16a,12a,12g_,12a,8g_,16g_,16f,8g_,16g_,16a,4b,8a,8g_,8f,16f,16e,8f,16f,16g_,4a,8g_,8f,4e#,8e#,16e#,16f,8g,16g,16a#,8b,8c1,8a#,16a#-1,16a#-1,8a#-1,16a#-1,16a#-1,8a#-1,16a#-1,16a#-1,8a#-1,8a#-1";
MusicWithoutDelay instrument(Soprano);          //o=5 means that the instrument will play at the 5th Octave. o=4 is default
MusicWithoutDelay instrument2(Bass);          //f=aeb, means all a's, e's, and b's are flats
Tone myTone;                                    //b=160, means the bpm(tempo) is 160, default is 100
Tone myTone2;
#define BUTTON_PIN 2       //Connect a tactile button switch (or something similar) from Arduino pin 2 to ground.
#define BUTTON_PIN2 3       //Connect a tactile button switch (or something similar) from Arduino pin 3 to ground.
#define BUTTON_PIN3 4       //Connect a tactile button switch (or something similar) from Arduino pin 3 to ground.

#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high
#define DEBOUNCE_MS 70     //A debounce time of 70 milliseconds usually works well for noisy button switches. if not, try 20.
Button pauseButton(BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the button
Button randomSkipButton(BUTTON_PIN2, PULLUP, INVERT, DEBOUNCE_MS);
Button reverseButton(BUTTON_PIN3, PULLUP, INVERT, DEBOUNCE_MS);

const int potPin = A1;
const int vibratingMotor = A0;
unsigned long motorMillis = 0;

int rgbLeds[] = {13, 12, 11};
int ledCursor = 0;
bool pState;
bool state;
bool stopped = true;
void setup() {
  // put your setup code here, to run once:
  myTone.begin(7);        //attach both pins to same speaker with one 1k resistor to pin 11,
  myTone2.begin(6);       //and another 1k resistor to pin 10.
  for (int i = 0; i < 3; i++) {
    pinMode(rgbLeds[i], OUTPUT);
  }
  pinMode(vibratingMotor, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long cMillis = millis();
  instrument.play(cMillis, myTone);
  instrument2.play(cMillis, myTone2);
  pauseButton.read();
  randomSkipButton.read();
  reverseButton.read();
  boundsCheck(instrument);
  boundsCheck(instrument2);
  if (instrument.isPaused() && instrument2.isPaused() && stopped) {
    Pause();
  }
  if (pauseButton.wasPressed()) {
    Pause();        // stop or play song
    stopped = false;
  }
  if (reverseButton.wasPressed()) {
    instrument.reverse();         //reverse direction of song
    instrument2.reverse();
  }
  if (randomSkipButton.wasPressed()) {   //skip to location in song depending on value of potentiometer
    int val = analogRead(potPin);
    val = map(val, 0, 1023, 0, instrument.getTotalTime());
    instrument.skipTo(val);
    val = analogRead(potPin);
    val = map(val, 0, 1023, 0, instrument2.getTotalTime());
    instrument2.skipTo(val);
  }
  if (instrument2.isNote()) {
    digitalWrite(vibratingMotor, HIGH);
    motorMillis = cMillis;
  }
  if (cMillis - motorMillis >= 40) {
    digitalWrite(vibratingMotor, LOW);
  }
  state = instrument.isNote();
  if (state != pState) {
    pState = state;
    if (pState) {
      digitalWrite(rgbLeds[ledCursor], LOW);
    }
    else {
      digitalWrite(rgbLeds[ledCursor], LOW);
      ledCursor++;
      if (ledCursor == 3) {
        ledCursor = 0;
      }
      digitalWrite(rgbLeds[ledCursor], HIGH);
    }
  }
  if (instrument.isRest()) {
    digitalWrite(rgbLeds[ledCursor], LOW);
  }
}
void boundsCheck(MusicWithoutDelay &m) {  //This function fixes songs that may have multiple instruments containing different TotalTimes
  if (m.isEnd()) {
    m.pause();
    stopped = true;
  }
}
void Pause() {
  instrument.pause();
  instrument2.pause();
}
