#include <CapTouch.h>
#include <SoftwareSerial.h>
int Echo = A4;
int Trig = A5;
int PirR = 2;
int PirL = 4;

CapTouch touch_0_1 = CapTouch(A1, A0);
float smoothed;

#define rxPin 30
#define txPin 3
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 100

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

int checkNobody = 0;
int checkTouch = 0;

int middleDistance = 0;
void forward() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW); digitalWrite(ENB, LOW);
  Serial.println("Stop!");
}

int Distance_test() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);
  Fdistance = Fdistance / 58;
  return (int)Fdistance;
}


void (*arr[])() = {happy, happy, happy, happy, happy, happy, happy, happy, happy, happy, happy, bak, bak, happy, happy, mad, turning, tired, happy, happy, happy, happy, die, mad};


void setup() {

  Serial.begin(9600);

  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);      // 9600 baud is chip communications speed
  delay(80);                //                 pause to allow LCD EEPROM to
  mySerial.print("?G420");   // set to LCD display geometry,  2 x 16 characters in this case
  delay(80);                //                 pause to allow LCD EEPROM to program
  mySerial.print("?Bff");    // set backlight to ff hex, maximum brightness (you can change this!)
  delay(80);                // pause to allow LCD EEPROM to program

  pinMode(PirR, INPUT);
  pinMode(PirL, INPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
}

void loop() {
  long total =  touch_0_1.readTouch(15);    //  read the sensor
  Serial.println(total);
  int leftPir = digitalRead(PirL);
  int rightPir = digitalRead(PirR);
  int ranIndex = rand() % 24;
  middleDistance = Distance_test();

  if (total > 350) {
    checkNobody = 0;
    checkTouch = 0;
    mySerial.print("?Bff");
    (*arr[ranIndex])();
    return;
  }

  if (middleDistance < 40 && middleDistance > 14) {
    checkNobody = 0;
    checkTouch = 0;
    mySerial.print("?Bff");
    mySerial.print("?f");
    //delay(30);
    mySerial.print("COME PLAY WITH ME!");
    //delay(100);
    forward();
  }

  else if (middleDistance < 14 && middleDistance > 12) {
    //right();
    //delay(10);
    checkTouch += 1;
    checkNobody = 0;
    if (checkTouch > 50) {
      mySerial.print("?f");
      mySerial.print("YOU ARE BORING!");
      left();
      delay(1600);
      forward();
      delay(1000);
      stop();
      delay(200);
      checkTouch = 0;
      return;
    } else {
    mySerial.print("?Bff");
    mySerial.print("?f");
    //delay(30);
    mySerial.print("TOUCH MY BACK!");
    //delay(100);
    return;
    }
    return;
  }

  else if (middleDistance < 12 && middleDistance > 1) {
    checkNobody = 0;
    checkTouch = 0;
    mySerial.print("?Bff");
    mySerial.print("?f");
    //delay(30);
    mySerial.print("DONT HURT ME!");
    //delay(100);
    back();
  }

  else if (middleDistance > 40 || middleDistance < 1) {
    checkTouch = 0;
    //stop();

    if (leftPir == 1 && rightPir == 0) {
      checkNobody = 0;
      mySerial.print("?Bff");
      //turns on screen
      mySerial.print("?f");
      //delay(30);
      mySerial.print("I WILL CATCH YOU!");
      //delay(100);
      left();
    } else if (leftPir == 0 && rightPir == 1) {
      checkNobody = 0;
      mySerial.print("?Bff");
      //turns on screen
      mySerial.print("?f");
      //delay(30);
      mySerial.print("I SEE YOU!");
      //delay(100);
      right();
    } else if (leftPir == 1 && rightPir == 1) {
      checkNobody = 0;
      mySerial.print("?Bff");
      stop();
      mySerial.print("?f");
      //delay(30);
      mySerial.print("TOUCH ME!");
      //delay(100);

      //turns on screen
    } else if (leftPir == 0 && rightPir == 0) {
      checkNobody += 1;
      stop();
      //Shutdown the screen
      mySerial.print("?f");
      //delay(30);
      mySerial.print("DONT LEAVE!");
      //delay(50);
      if (checkNobody > 100) {
        mySerial.print("?f");
        mySerial.print("?B00");
      } else {
        mySerial.print("?Bff");
      }
    }
  }
}

void tired() {
  mySerial.print("?f");
  delay(30);
  mySerial.print("LIFE SUCK!");
  delay(100);
  left();
  delay(2000);
  forward();
  delay(1000);
  stop();
  delay(4000);
}

void turning() {
  mySerial.print("?f");
  delay(30);
  mySerial.print("BUGS ON MY TAIL!");
  delay(100);
  left();
  delay(3000);
  stop();
  delay(1000);
}

void bak() {
  mySerial.print("?f");
  delay(30);
  mySerial.print("?x04?y1");
  mySerial.print("^");
  mySerial.print("?x15?y1");
  mySerial.print("^");
  mySerial.print("?x09?y2");
  mySerial.print("v");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  back();
  delay(100);
  right();
  delay(100);
  back();
  delay(100);
  mySerial.print("?x09?y2");
  mySerial.print("O");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  forward();
  delay(100);
  right();
  delay(100);
  forward();
  delay(100);
  mySerial.print("?x09?y2");
  mySerial.print("v");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  back();
  delay(100);
  right();
  delay(100);
  back();
  delay(100);
  mySerial.print("?x09?y2");
  mySerial.print("O");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  forward();
  delay(100);
  right();
  delay(100);
  forward();
  delay(100);
}

void mad() {
  mySerial.print("?f");
  delay(30);
  mySerial.print("DONT TOUCH MY ASS!");
  delay(100);
  forward();
  delay(900);
  stop();
  delay(1500);
}

void happy() {
  mySerial.print("?f");
  delay(30);
  mySerial.print("?x04?y1");
  mySerial.print("^");
  mySerial.print("?x15?y1");
  mySerial.print("^");
  mySerial.print("?x09?y2");
  mySerial.print("o");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  mySerial.print("?B00");
  right();
  delay(100);

  mySerial.print("?Bff");
  mySerial.print("?x04?y1");
  mySerial.print("O");
  mySerial.print("?x15?y1");
  mySerial.print("O");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  mySerial.print("?B00");
  right();
  delay(100);
  mySerial.print("?Bff");

  mySerial.print("?Bff");
  mySerial.print("?x04?y1");
  mySerial.print("^");
  mySerial.print("?x15?y1");
  mySerial.print("^");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  mySerial.print("?B00");
  right();
  delay(100);
  mySerial.print("?Bff");

  mySerial.print("?Bff");
  mySerial.print("?x04?y1");
  mySerial.print("O");
  mySerial.print("?x15?y1");
  mySerial.print("O");
  mySerial.print("?x19?y3");
  left();
  delay(100);
  mySerial.print("?B00");
  right();
  delay(100);
  mySerial.print("?Bff");
  return;
}

void die() {
  stop();
  mySerial.print("?f");
  delay(30);
  mySerial.print("YOU ARE POISON!");
  delay(3000);
  mySerial.print("?f");
  delay(30);
  mySerial.print("?x04?y1");
  mySerial.print("X");
  mySerial.print("?x15?y1");
  mySerial.print("X");
  mySerial.print("?x09?y2");
  mySerial.print("__");
  mySerial.print("?x11?y3");
  delay(3000);
  mySerial.print("?B00");
  delay(7000);
}

