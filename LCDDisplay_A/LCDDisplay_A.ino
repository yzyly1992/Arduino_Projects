#include <SoftwareSerial.h>            // we need to include this library !

#define rxPin 30  // rxPin is immaterial - not used - just make this an unused Arduino pin number
#define txPin 3 // txPin is the one needed for the LCD - we'll use Digital Pin A0/14 to send serial data to the LCD
// mySerial is connected to the TX pin so mySerial.print commands are used
// one could just as well use the software mySerial library to communicate on another pin
// we're using SoftwareSerial so that we can save pins 0&1 for the BUB

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);    // let SoftwareSerial know what pins we'll use

void setup()
{
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);      // 9600 baud is chip communications speed
  delay(80);                //                 pause to allow LCD EEPROM to
  mySerial.print("?G420");   // set to LCD display geometry,  2 x 16 characters in this case
  delay(80);                //                 pause to allow LCD EEPROM to program
  mySerial.print("?ff");    // set backlight to ff hex, maximum brightness (you can change this!)
  delay(80);                // pause to allow LCD EEPROM to program
}

void loop()
{
  mySerial.print("?f");                   // clear the LCD
  delay(30);
  mySerial.print("I");               // display "hello world" on the LCD via a SerialPrint
  delay(1000);                               // pause so that we can read the message

  mySerial.print("?f");                   // clear the LCD
  delay(30);
  mySerial.print("?x04?y1");              // cursor to 5th character of line 1 (x=4, y=1)
  delay(30);
  mySerial.print("AM");               // display "hello world" on the LCD via a SerialPrint
  delay(1000);                               // pause so that we can read the message

  mySerial.print("?f");                   // clear the LCD
  delay(30);
  mySerial.print("?x08?y2");              // cursor to 5th character of line 1 (x=4, y=1)
  delay(30);
  mySerial.print("REALLY");               // display "hello world" on the LCD via a SerialPrint
  delay(1000);

  mySerial.print("?f");                   // clear the LCD
  delay(30);
  mySerial.print("?x12?y3");              // cursor to 5th character of line 1 (x=4, y=1)
  delay(30);
  mySerial.print("HUNGRY");               // display "hello world" on the LCD via a SerialPrint
  delay(1000);

}

