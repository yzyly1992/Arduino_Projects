const int LEDPin = 11;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(4);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      if (buttonPushCounter > 4) {
        buttonPushCounter = 0;
      }
    }
  } else {

    if (buttonPushCounter == 1) {

      for (int i = 0; i < 200; i++) {
        analogWrite(LEDPin, i);
        delay(3);
      }

      for (int i = 200; i > 0; i--) {
        analogWrite(LEDPin, i);
        delay(3);
      }
    }

    if (buttonPushCounter == 2) {
      for (int i = 0; i<150; i++){
        analogWrite(LEDPin, i);
        delay(40);
        analogWrite(LEDPin, i+100);
        delay(15);
      }
      for (int i = 250; i>100; i--){
        analogWrite(LEDPin, i);
        delay(15);
        analogWrite(LEDPin, i-100);
        delay(40);
      }
      
      delay(10);
    }

    if (buttonPushCounter == 3) {
      for (int i = 0; i<255; i++){
        analogWrite(LEDPin, i);
        delay(20);
        analogWrite(LEDPin, 255-i);
        delay(10);
      }
      for (int i = 255; i>0; i--){
        analogWrite(LEDPin, i);
        delay(20);
        analogWrite(LEDPin, 255-i);
        delay(10);
      }
      delay(10);
    }

    if (buttonPushCounter == 4) {
      for (int i = 50; i<200; i++){
        analogWrite(LEDPin, i);
        delay(3);
        analogWrite(LEDPin, 0);
        delay(8);
      }

      for (int i = 200; i>50; i--){
        analogWrite(LEDPin, i);
        delay(3);
        analogWrite(LEDPin, 0);
        delay(8);
      }


      
      delay(10);
    }
    
  }
  delay(10);
  // controls the speed
  lastButtonState = buttonState;

}
