
/* Print a random string to a character LCD
* String sketch - demonstrates an array of strings and 
* printing a random string
*/

#include <SoftwareSerial.h>

const int rxPin = 30;  // rxPin is not used - make this an invalid Arduino pin number
const int txPin = 8; // pin 14 is analog pin A0, on a BBB or Educato 
                      // just use a servo cable in the analog block
                      // note that SoftwareSerial will work on any pin though

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);


// Note that these strings are going into Arduino RAM. 
// An Atmega328-based Arduino has 2K of RAM so long strings here 
// can fill up the RAM and cause the board to stop functioning.
// Use PROGMEM for much longer texts (30K)
char* myStrings[]={"Bill", "Nancy", "Frank", "Sally", "Spot","Tom"};

int strCount;

void setup(){

    pinMode(txPin, OUTPUT);
    mySerial.begin(9600);      // 9600 baud is chip comm speed

    mySerial.print("?G420");   // set display geometry,  2 x 16 characters in this case
    delay(100);                // pause to allow LCD EEPROM to program

    mySerial.print("?Bff");    // set backlight to ff hex, maximum brightness
    delay(100);                // pause to allow LCD EEPROM to program

    mySerial.print("?s6");     // set tabs to six spaces
    delay(1000);               // pause to allow LCD EEPROM to program

}

void loop(){

  static int r,s=5,t=10,u=15;
  r++;
  s++;
  t++;
  u++;

    // print a random string on line 1

    mySerial.print("?f");  // clear the screen
    mySerial.print("?a");
    mySerial.print(r);
    mySerial.print("?x00?y3");
    mySerial.print(s);
    if (t<10) {
      mySerial.print("?x19?y0");
      mySerial.print(t);
    }
    else if (t < 100) {
      mySerial.print("?x18?y0");
      mySerial.print(t);
    }
    else if (t < 1000) {
      mySerial.print("?x17?y0");
      mySerial.print(t);
    }
    else if (t < 10000) {
      mySerial.print("?x16?y0");
      mySerial.print(t);
    }

    delay(100);
    
    
//    int a =  random(6);      // choose a random number from 0 to 5
//    mySerial.print("    ");
//    mySerial.print(myStrings[a]);  // print the string on line 1

//    mySerial.println("?x00?y1");      // move cursor to beginning of line 2

//    strCount =  (strCount + 1) % 6;  // modulo operator wraps the count
//    mySerial.println(myStrings[strCount]); // print the strings in order
                                           // on line 2 

    delay(1000);
}
