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
  mySerial.print("?f");                
  delay(30);
  mySerial.print("?x04?y1");              
  mySerial.print("X");          
  mySerial.print("?x15?y1"); 
  mySerial.print("X");
  mySerial.print("?x09?y2"); 
  mySerial.print("__");
  mySerial.print("?x11?y3"); 
  delay(2000);

  mySerial.print("?f");                
  delay(30);
  mySerial.print("?x04?y1");              
  mySerial.print("^");          
  mySerial.print("?x15?y1"); 
  mySerial.print("^");
  mySerial.print("?x09?y2"); 
  mySerial.print("o");
  mySerial.print("?x19?y3"); 
  delay(500); 
  mySerial.print("?x04?y1");              
  mySerial.print("O");          
  mySerial.print("?x15?y1"); 
  mySerial.print("O");
  mySerial.print("?x19?y3"); 
  delay(500);
  mySerial.print("?x04?y1");              
  mySerial.print("^");          
  mySerial.print("?x15?y1"); 
  mySerial.print("^");
  mySerial.print("?x19?y3"); 
  delay(500); 
  mySerial.print("?x04?y1");              
  mySerial.print("O");          
  mySerial.print("?x15?y1"); 
  mySerial.print("O");
  mySerial.print("?x19?y3"); 
  delay(500);
  mySerial.print("?x19?y3"); 
  delay(2000);     

}

