
int SWPin = 2;
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

void style_1(void) {
  unsigned char j;
  for(j=4; j<=13; j++){
    digitalWrite(j, HIGH);
  }
  delay(100);

  for(j=4; j<=13; j++){
    digitalWrite(j, LOW);
  }
  delay(100);
}

void style_2(void){
  unsigned char j;
  for(j=4; j<=13; j++){
    digitalWrite(j, HIGH);
    delay(20);
    digitalWrite(j, LOW);
    delay(20);
  }

  for(j=12; j>=4; j--){
    digitalWrite(j, HIGH);
    delay(20);
    digitalWrite(j, LOW);
    delay(20);
  }
  delay(20);
}

void style_3(void) {
  unsigned char j;
  for(j=4; j<=13; j+=2){
    digitalWrite(j, HIGH);
    delay(20);
  }
  for(j=13; j>=4; j-=2){
    digitalWrite(j, HIGH);
    delay(20);
  }
  for(j=5; j<=13; j+=2){
    digitalWrite(j, LOW);
    delay(20);
  }
  for(j=12; j>=4; j-=2){
    digitalWrite(j, LOW);
    delay(20);
  }
  delay(20);
}

void style_4(void) {
  unsigned char j;
  for(j=4; j<=13;j++) {
    digitalWrite(j, HIGH);
    delay(20);
  }
  for(j=13; j>=4;j--) {
    digitalWrite(j, LOW);
    delay(20);
  }
  delay(20);
}

void style_5(void) {
  unsigned char j, k;
  k=1;
  for(j=8; j>=4; j--) {
    digitalWrite(j, HIGH);
    digitalWrite(j+k,HIGH);
    delay(20);
    k += 2;
  }
  k=9;
  for (j=4; j<=8; j++) {
    digitalWrite(j,LOW);
    digitalWrite(j+k,LOW);
    delay(20);
    k -= 2;
  }
  delay(20);
}

void style_6(void) {
  unsigned char j,k;
  k=9;
  for(j=4; j<=8; j++) {
    digitalWrite(j,HIGH);
    digitalWrite(j+k, HIGH);
    delay(20);
    digitalWrite(j,LOW);
    digitalWrite(j+k, LOW);
    k-=2;
  }
  k=3;
  for(j=7; j>=4; j--) {
    digitalWrite(j,HIGH);
    digitalWrite(j+k, HIGH);
    delay(20);
    digitalWrite(j,LOW);
    digitalWrite(j+k, LOW);
    k+=2;
  }
  delay(20);
}

void style_7(void) {
  unsigned char i;
  unsigned char n;
  for(i=5; i>=1; i--) {
    for(n=i; n>=1; n--) {
      style_1();
    }
    delay(400);
  }
  delay(20);
}

void style_8(void) {
  unsigned int i;
  for(i=0; i<255; i+=2) {
    analogWrite(9, i);
    analogWrite(10, i);
    analogWrite(11, i);
    delay(20);
  }

  for(i=255; i>0; i-=2) {
    analogWrite(9, i);
    analogWrite(10, i);
    analogWrite(11, i);
    delay(20);
  }
  delay(20);
}



void setup() {
  unsigned char i;
  for(i=4; i<=13; i++) {
    pinMode(i,OUTPUT);
  }  
   pinMode(SWPin, INPUT);
   pinMode(A3, OUTPUT);
}

void loop() {
  buttonState=digitalRead(SWPin);
  if(buttonState != lastButtonState){
    if(buttonState == HIGH){
      buttonPushCounter++;
      if(buttonPushCounter>8){
        buttonPushCounter = 1;
      }}}else{
      
      if(buttonPushCounter == 1) {
          style_1();
          delay(50);
        }
      
      if(buttonPushCounter == 2) {
          style_2();
          delay(50);
        }

      if(buttonPushCounter == 3) {
          style_3();
          delay(50);
        }

      if(buttonPushCounter == 4) {
          style_4();
          delay(50);
        }

      if(buttonPushCounter == 5) {
          style_5();
          delay(50);
        }

      if(buttonPushCounter == 6) {
          style_6();
          delay(50);
        }

      if(buttonPushCounter == 7) {
          style_7();
          delay(50);
        }
      if(buttonPushCounter == 8) {
          style_8();
          delay(50);
        }
      }
  lastButtonState = buttonState;
}

