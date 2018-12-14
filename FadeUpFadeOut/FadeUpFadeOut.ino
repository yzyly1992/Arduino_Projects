int buttonState = 0;
int j,k,l = 0;
bool jOrder = true;
bool kOrder = true;
bool lOrder = true;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(2);
  if(buttonState == HIGH) {
    j=0;
    k=0;
    l=0;
    lOrder = true;
    jOrder = true;
    kOrder = true;
  }
  if (jOrder == true) {
    analogWrite(9, j);
    j++;
    if (j >= 255){
      jOrder = false;
      j=255;
    }
  }
  else if(jOrder == false){
    analogWrite(9, j);
    j--;
    if(j<=0){
      jOrder = true;
      j=0;
    }
  }
  
  if (kOrder == true) {
    analogWrite(10, k);
    k+=2;
    if (k >= 255){
      kOrder = false;
      k=255;
    }
  }
  else if(kOrder == false){
    analogWrite(10, k);
    k-=2;
    if (k <= 0){
      kOrder = true;
      k=0;
    }
  }

  if (lOrder == true) {
    analogWrite(11, l);
    l+=8;
    if (l >= 255){
      lOrder = false;
      l=255;
    }
  }
  else if(kOrder == false){
    analogWrite(11, l);
    l-=8;
    if (l <= 0){
      lOrder = true;
      l=0;
    }
  }
  delay(5);

}
