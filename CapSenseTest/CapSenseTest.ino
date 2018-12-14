#include <CapSense.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008/updated 2012 for libraries
 * Uses a high value resistor e.g. 1M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 500K - 20M. 
 * Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

// you can change the below pin assignements - these are for example purposes
CapSense   cs_4_2 = CapSense(4,2);   // 1M resistor between pins 4 & 2, pin 2 is sensor pin
// you can sense more than one probe (metal plate), uncomment below
//CapSense   cs_4_6 = CapSense(4,6); // 1M resistor between pins 4 & 6, pin 6 is sensor pin
//CapSense   cs_4_8 = CapSense(4,8); // 1M resistor between pins 4 & 8, pin 8 is sensor pin

void setup()                    
{

    Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    // this software allows for 3 capacative sensors - each
    // cs_4_2.capSense(30) reads each sensor 30 times - shorter reads work almost as well 
    long CapSensor1_val =  cs_4_2.capSense(30);        // Cap_sensor 1 (metal piece #1)
    //    long CapSensor2_val =  cs_4_6.capSense(30);  // Cap_sensor 2 (metal piece #2)
    //    long CapSensor3_val =  cs_4_8.capSense(30);  // Cap_sensor 3 (metal piece #3)

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.println(CapSensor1_val);        // print sensor output 1
    //    Serial.print("\t");
    //    Serial.print(CapSensor2_val);    // print sensor output 2
    //    Serial.print("\t");
    //    Serial.println(CapSensor3_val);  // print sensor output 3

    delay(10);                             // arbitrary delay to limit data to serial port 
}


