int pin = 8;

void setup() {
  pinMode(pin, OUTPUT);

}

void loop() {
analogWrite(pin,128);
delay(500);

for(int a=0; a <= 255; a++){
  analogWrite(3,a);
  delay(2);  
  }

for(int a = 255; a>=0; a--){
  analogWrite(3,a);
  delay(2);
  }
delay(100);
}

