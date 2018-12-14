/*  2Switches4Patterns.pde
    Read two momentary switches and branch program to four outputs (patterns)
    depending on switch states.
    Also demonstrates blinking LEDs.

  Hardware setup
  2 Momentary switches with pulldowns - connected to Educato (Arduino) pins 2 & 3
  10 LEDs with the long lead pointing toward the Educato board
  from pins 4,5,6,7,8,9,10,11,12,13 connected to anode (long lead of LEDs with cathode (short lead)
  connected to a 470 ohm or 1k series resistor to ground.
*/

// this is a comment - the computer ignores it
// it doesn't effect the program in any way
// but it makes it easier for humans to read
/*  This line is also "commented out"  */

const int SwitchPin1 = 2;   // define the pin numbers for the switches
const int SwitchPin2 = 3;   // define the pin numbers for the switches

const int LED0 = 4;         // define the pin numbers for the LEDs
const int LED1 = 5;
const int LED2 = 6;
const int LED3 = 7;
const int LED4 = 8;
const int LED5 = 9;
const int LED6 = 10;
const int LED7 = 11;
const int LED8 = 12;
const int LED9 = 13;

int sw1state = 0;               // variable for reading the pin status
int sw2state = 0;               // variable for reading the pin status
int state;
int lastState;

void setup() {
  Serial.begin(9600);           // initialize serial transmission for debugging
  // you will note that the pins are contiguous, I used all of the PWM pins so
  // that all of the LEDs may be dimmed if you wish.

  pinMode(LED0, OUTPUT);           // declare pin 5 as output for lighting LEDs
  pinMode(LED1, OUTPUT);           // declare pin 6 as output for lighting LEDs
  pinMode(LED2, OUTPUT);           // declare pin 7 as output for lighting LEDs
  pinMode(LED3, OUTPUT);           // declare pin 8 as output for lighting LEDs
  pinMode(LED4, OUTPUT);           // declare pin 9 as output for lighting LEDs
  pinMode(LED5, OUTPUT);          // declare pin 10 as output for lighting LEDs
  pinMode(LED6, OUTPUT);          // declare pin 11 as output for lighting LEDs
  pinMode(LED7, OUTPUT);          // declare pin 12 as output for lighting  LEDs
  pinMode(LED8, OUTPUT);          // declare pin 12 as output for lighting  LEDs
  pinMode(LED9, OUTPUT);          // declare pin 12 as output for lighting  LEDs


  pinMode(SwitchPin1, INPUT);   // declare SwitchPin1 as input - not really necessary, pins default to inputs
  pinMode(SwitchPin2, INPUT);   // not really necessary, pins default to inputs
}

void loop() {
  sw1state = digitalRead(SwitchPin1);    // read switch 1
  sw2state = digitalRead(SwitchPin2);    // read switch 2

  checkToSeeIfSwitchesHaveChanged();     // try and comment this out to 
                                         // and see what changes in your program

  Serial.print(sw1state);       // print switch states for debugging
  Serial.print("   ");          // add some space for legibility
  Serial.println(sw2state);     // note "println" instead of "print"
  // adds  carriage return for new line in the serial monitor


  if ((sw1state == LOW) && (sw2state == LOW)) {  // neither switch pressed - default state
    digitalWrite(LED0, HIGH);       // turn LED0 on
    delay(50);                          // delay to make a visible blink
    digitalWrite(LED1, LOW);        // turn LED1 off
    delay(50);                          // delay to make a visible blink
    digitalWrite(LED0, LOW);        // turn LED0 off
    delay(50);                          // delay to make a visible blink
    digitalWrite(LED1, HIGH);       // turn LED1 on
    delay(50);                      // delay to make a visible blink

  }

  else if ((sw1state == LOW) && (sw2state == HIGH)) {   // the second switch pressed
    digitalWrite(LED2, HIGH);       // turn LED2 on
    digitalWrite(LED3, LOW);        // turn LED3 off
    delay(100);                     // delay to make a visible blink
    digitalWrite(LED2, LOW);        // turn LED2 off
    digitalWrite(LED3, HIGH);       // turn LED3 on
    delay(100);                     // delay to make a visible blink
  }

  else if ((sw1state == HIGH) && (sw2state == LOW)) {   // the first switch pressed
    digitalWrite(LED0, HIGH);
    digitalWrite(LED3, LOW);
    delay(100);
    digitalWrite(LED0, LOW);
    digitalWrite(LED3, HIGH);
    delay(100);
  }

  else if ((sw2state == HIGH) && (sw2state == HIGH)) {  // both switches pressed
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    delay(100);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(100);
  }
}

void allLEDsOff() {
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  digitalWrite(LED9, LOW);
}

void checkToSeeIfSwitchesHaveChanged() {
  // this function just turns off all LEDs when the switches change,
  // otherwise some LEDs might be left ON from other patterns
  // don't worry if you don't understand this now.
  lastState = state;                  // update lastState variable to compare 
                                      // with new state
  state = sw2state + (2 * sw1state);  // encode the new switch states
  if (lastState != state) {           // if true the switches have changed
    allLEDsOff();                     // then turn off all the LEDs
  }
}
