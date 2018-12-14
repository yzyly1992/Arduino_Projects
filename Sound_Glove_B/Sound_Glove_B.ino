#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

AudioPlaySdWav           playWav1;
// Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
AudioOutputI2S           audioOutput;
//AudioOutputSPDIF       audioOutput;
//AudioOutputAnalog      audioOutput;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14
#define POD_PIN 20
#define TRI_PIN 17
#define ECO_PIN 16
char* fileNameArray[] = {"01.wav", "02.wav", "03.wav", "04.wav", "05.wav", "06.wav", "07.wav", "08.wav"};
unsigned long  lastTime;

const unsigned int maxDuration = 12500; // around 6.5 feet
//                                      // the sensor gets flaky at greater distances.
const int speed_of_sound_uS_CM = 29;    // speed of sound microseconds per centimeter
unsigned int SonarCloseness;
unsigned int duration, lastDuration;
unsigned int distance_CM;
int dist;

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

void setup() {
  //Serial.begin(9600);
  pinMode(TRI_PIN, OUTPUT);
  pinMode(ECO_PIN, INPUT);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      //Serial.println("Unable to access the SD card");
      delay(500);
    }
  }


  //Serial.begin(9600);
  //Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    //Serial.println("Couldnt start");
    while (1);
  }
  //Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  //Serial.print("Range = "); Serial.print(2 << lis.getRange());
  //Serial.println("G");
}

int readSensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(4);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(380);  // wait as long as possible for transmit transducer to stop ringing
  // before looking for a return pulse
  // if you get zeros in your output reduce 400 by a little, say 390
  duration = pulseIn(echoPin, HIGH, 10000);
  // third parameter is the timeout - the sensor
  // has a really long timeout that can slow down your
  // loop significantly if sensor doesn't find an echo

  distance_CM = (duration / 2) / speed_of_sound_uS_CM;
  // for inches change divide distance_CM by 2.5
  //Serial.print(distance_CM);  // comment out for better performance
  return distance_CM;
}

void playFile(const char *filename)
{
  //Serial.print("Playing file: ");
  //Serial.println(filename);

  dist = readSensor(TRI_PIN, ECO_PIN);
  delay(200);
  //Serial.println(dist);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(dist * 80);

  // Simply wait for the file to finish playing.
  //while (playWav1.isPlaying()) {
  // uncomment these lines if you audio shield
  // has the optional volume pot soldered
  float vol = map(dist, 0, 180, 0.8, 0);
  sgtl5000_1.volume(vol);

}


void loop() {
  if (millis() - lastTime > 1000) {
    lis.read();
    sensors_event_t event;
    lis.getEvent(&event);

    //float controlPotVal = analogRead(POD_PIN);
    int mapped = map(event.acceleration.y, -9, 4, 1, 9);
    //if (millis() - lastTime > 3000) {
    //Serial.println(mapped);
    playArrayNamesControledByPot(mapped);
    //lastTime = millis();
    //}
    lastTime = millis();
  }
}

void playArrayNamesControledByPot(int fileNo) {
  //int static lastFileNo;
  //if (!playWav1.isPlaying()) {
  //Serial.println(fileIndex);
  //if (fileNo != lastFileNo) {
    dist = readSensor(TRI_PIN, ECO_PIN);
    delay(200);
    if (dist == 0) {
      playWav1.play(fileNameArray[fileNo]);
      delay(200);
      //Serial.print("play 0 distance");
      return;
    }
    //Serial.print("dist:");
    //Serial.println(dist);
    float vol = (map(dist, 0, 40, 7, 1) / 10.0);
    //Serial.print("vol:");
    //Serial.println(vol);
    playWav1.play(fileNameArray[fileNo]);
    delay(dist * 100);
    
    sgtl5000_1.volume(vol);
  //  lastFileNo = fileNo;
  //}
}

