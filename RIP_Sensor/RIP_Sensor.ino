/*  PIR Sensor (Passive Infrared Sensor)

  Remember to wait at least a minute for output to stabilize! May require two minutes!
*/

const int PIRpin = 4;  // or change to pin you are using

void setup() {
  pinMode(PIRpin, INPUT);
  Serial.begin(9600);
}

void loop() {

  int sensorValue = digitalRead(PIRpin);

  Serial.println(sensorValue);  // print out the value you read:
  delay(250);                   // delay for readability
}
