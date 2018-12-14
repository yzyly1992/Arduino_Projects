#include <CapTouch.h>
//#include <Servo.h> //servo library
//Servo myservo; // create servo object to control servo
int Echo = A4;
int Trig = A5;
int PirR = 2;
int PirL = 4;

CapTouch touch_0_1 = CapTouch(1, 0);
float smoothed;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 150
int middleDistance = 0;
void forward() {
  analogWrite(ENA, carSpeed); analogWrite(ENB, carSpeed); digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}
void back() {
  analogWrite(ENA, carSpeed); analogWrite(ENB, carSpeed); digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  Serial.println("Back");
}
void left() {
  analogWrite(ENA, carSpeed); analogWrite(ENB, carSpeed); digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  Serial.println("Left");
}
void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
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
//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW); delayMicroseconds(2); digitalWrite(Trig, HIGH); delayMicroseconds(20); digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH); Fdistance = Fdistance / 58;
  return (int)Fdistance;
}
void setup() {
  //myservo.attach(3); // attach servo on pin 3 to servo object
  Serial.begin(9600);
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
  
  long start = millis();                    // scheme to time performance, delete at will
  long total =  touch_0_1.readTouch(15);    //  read the sensor
  long elapsedTime =  millis() - start;     // scheme to time performance, delete at will

  // simple lowpass filter to take out some of the jitter
  // change parameter (0 is min, .99 is max) or eliminate to suit
  // you need a different "smoothed" variable for each sensor is using more than one
  smoothed = smooth(total, .95, smoothed);




  //myservo.write(90); //setservo position according to scaled value delay(500);
  int leftPir = digitalRead(PirL);
  int rightPir = digitalRead(PirR);
  middleDistance = Distance_test();

  if (middleDistance < 25 && middleDistance > 14) {
    forward();
  }

  else if (middleDistance < 14 && middleDistance > 12) {
    stop();
  }

  else if (middleDistance < 12 && middleDistance > 1) {
    back();
  }

  else if (middleDistance > 25 || middleDistance < 1) {
    stop();

    if (leftPir == 1 && rightPir == 0) {
      left();
      delay(200);
      //turns on screen
    } else if (leftPir == 0 && rightPir == 1) {
      right();
      delay(200);
      //turns on screen
    } else if (leftPir == 1 && rightPir == 1) {
      stop();
      delay(20);
      //turns on screen
    } else if (leftPir == 0 && rightPir == 0) {
      //Shutdown the screen
    }
  }
}


// simple lowpass filter
// requires recycling the output in the "smoothedVal" param
float smooth(float data, float filterVal, float smoothedVal) {

  if (filterVal > 1) {     // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0) {
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return smoothedVal;
}



