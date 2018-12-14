
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
  delay(200);
  
  for(j=4; j<=13; j++){
    digitalWrite(j, HIGH);
  }
  delay(100);

  for(j=4; j<=13; j++){
    digitalWrite(j, LOW);
  }
  delay(200);
}

void style_2(void){
  unsigned char j;
  for(j=4; j<=13; j++){
    digitalWrite(j, HIGH);
    delay(200);
    digitalWrite(j, LOW);
    delay(200);
  }

  for(j=12; j>=4; j--){
    digitalWrite(j, HIGH);
    delay(200);
    digitalWrite(j, LOW);
    delay(200);
  }
}

void style_3(void) {
  unsigned char j;
  for(j=4; j<=13; j+=2){
    digitalWrite(j, HIGH);
    delay(200);
  }
  for(j=13; j>=4; j-=2){
    digitalWrite(j, HIGH);
    delay(200);
  }
  for(j=5; j<=13; j+=2){
    digitalWrite(j, LOW);
    delay(200);
  }
  for(j=12; j>=4; j-=2){
    digitalWrite(j, LOW);
    delay(200);
  }
  
}

void style_4(void) {
  unsigned char j;
  for(j=4; j<=13;j++) {
    digitalWrite(j, HIGH);
    delay(200);
  }
  for(j=13; j>=4;j--) {
    digitalWrite(j, LOW);
    delay(200);
  }
}

void style_5(void) {
  unsigned char j, k;
  k=1;
  for(j=8; j>=4; j--) {
    digitalWrite(j, HIGH);
    digitalWrite(j+k,HIGH);
    delay(400);
    k += 2;
  }
  k=9;
  for (j=4; j<=8; j++) {
    digitalWrite(j,LOW);
    digitalWrite(j+k,LOW);
    delay(400);
    k -= 2;
  }
}

void style_6(void) {
  unsigned char j,k;
  k=9;
  for(j=4; j<=8; j++) {
    digitalWrite(j,HIGH);
    digitalWrite(j+k, HIGH);
    delay(400);
    digitalWrite(j,LOW);
    digitalWrite(j+k, LOW);
    k-=2;
  }
  k=3;
  for(j=7; j>=4; j--) {
    digitalWrite(j,HIGH);
    digitalWrite(j+k, HIGH);
    delay(400);
    digitalWrite(j,LOW);
    digitalWrite(j+k, LOW);
    k+=2;
  }
}



void setup() {
  unsigned char i;
  for(i=4; i<=13; i++) {
    pinMode(i,OUTPUT);
  }  
   pinMode(SWPin, INPUT);
}

void loop() {
  buttonState=digitalRead(SWPin);
  if(buttonState != lastButtonState){
    if(buttonState == HIGH){
      buttonPushCounter++;
      if(buttonPushCounter>6){
        buttonPushCounter = 1;
      }
      if(buttonPushCounter==1) {
        style_1();
        delay(50);
      }else if(buttonPushCounter==2) {
        style_2();
        delay(50);
      }else if(buttonPushCounter==3) {
        style_3();
        delay(50);
      }else if(buttonPushCounter==4) {
        style_4();
        delay(50);
      }else if(buttonPushCounter==5) {
        style_5();
        delay(50);
      }else if(buttonPushCounter==6) {
        style_6();
        delay(50);
      }
    }
    lastButtonState = buttonState;
  }
}

