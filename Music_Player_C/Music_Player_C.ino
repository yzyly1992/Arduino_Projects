const int speakerPin = 10;
const int sensPin1 = A0;
const int sensPin2 = A1;
const int sensPin3 = A2;
const int sensPin4 = A3;

int sensVal1;
int sensVal2;
int sensVal3;
int sensVal4;
int mapVal1;
int mapVal2;
int mapVal3;
int mapVal4;
// Relative values are used here so you have to add 60 to 100 to them to get them
// into a nice audio range - added below
//int melody[] = {
   //1, 3, 5, 6, 8, 13, 10, 11, 13, 8, 11, 6, 6, 6, 5, 5, 3, 5, 3, 5, 1 };

// major scale 
//int melody[] = {
  //1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 18, 20, 22, 24, 25};

// mario midi 
int melody[] = {
   10, 10, 10, 8, 10, 12, 5, 8, 5, 3, 6, 7, 7, 6, 5, 10, 12, 13, 11, 12, 10, 8, 9, 7, 8, 5, 3, 6, 7, 7, 6, 5, 10, 12, 13, 11, 12, 10, 9, 8, 7, 12, 11, 11, 10, 10, 5, 6, 8, 6, 8, 9, 12, 11, 11, 10, 10, 15, 15, 12,11,11,10,10,5,6,8,6,8,9,10,9,8,8,8,8,8,9,10,8,6,5,8,8,8,8,9,10};
 
// find the last note in the array index
int melodyMaxIndex = sizeof(melody) / sizeof(melody[0]);   


void setup() {       
    Serial.begin(9600);          // init. serial at 9600 baud
}

void loop() {
sensVal1 = analogRead(sensPin1);   // read the sensor
sensVal2 = analogRead(sensPin2);
sensVal3 = analogRead(sensPin3);
Serial.print(sensVal1, sensVal2);           // print the "raw" value
Serial.print("   ");             // print some spaces for clarity

// map melody to whole pot rotation
 mapVal1 = map(sensVal1, 0, 1023, 0, melodyMaxIndex);
 mapVal2 = map(sensVal2, 0, 1023, 100, 500);
 mapVal3 = map(sensVal3, 0, 1023, 0, 1);
 mapVal4 = map(sensVal4, 0, 1023, 0, 100);
Serial.println(mapVal1);
// the line below generates the frequecy of notes using the math for the well tempered scale
// which is the twelfth root of two. - Google that in Wikipedia for an explanation.
float note = pow(2+(float)mapVal3, ((float)( melody[mapVal1] + sensVal2)) / 12);   // add 100 to get pitch into better range
tone(speakerPin, note);       
 delay(mapVal4);
}
