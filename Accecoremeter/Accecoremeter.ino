/* 3-axis analog accelerometer sketch
 *  works only on analog accelerometers - will not work with I2C or SPI based devices
 */

// sketch to read x, y, & z values of an MMA7361LC based analog-output accelerometer.

int y_axis = 0;
int x_axis = 0;
const int X_Pin = A4;  // arduino pin for x axis
const int Y_Pin = A5;  // arduino pin for y axis


void setup()
{
    Serial.begin(9600);    // open serial port to laptop to print values
}

void loop() 
{
    x_axis = analogRead(X_Pin); 
    Serial.print("  x = ");       
    Serial.println(x_axis, DEC);  
    y_axis = analogRead(Y_Pin);  
    Serial.print("  y = ");        
    Serial.println(y_axis, DEC);            // note "println" to add carriage return

    delay(300);                     // delay feel free to reduce or eliminate in other sketches
}
