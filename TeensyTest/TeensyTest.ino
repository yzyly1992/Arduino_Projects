#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=161,509
AudioPlaySdWav           playSdWav2;     //xy=166,443
AudioPlaySdWav           playSdWav3;     //xy=169,378
AudioPlaySdWav           playSdWav4;     //xy=173,313
AudioMixer4              mixer2;         //xy=516,262
AudioMixer4              mixer1;         //xy=517,362
AudioOutputI2S           i2s1;           //xy=791,280
AudioConnection          patchCord1(playSdWav1, 0, mixer2, 3);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 3);
AudioConnection          patchCord3(playSdWav2, 0, mixer2, 2);
AudioConnection          patchCord4(playSdWav2, 1, mixer1, 2);
AudioConnection          patchCord5(playSdWav3, 0, mixer2, 1);
AudioConnection          patchCord6(playSdWav3, 1, mixer1, 1);
AudioConnection          patchCord7(playSdWav4, 0, mixer2, 0);
AudioConnection          patchCord8(playSdWav4, 1, mixer1, 0);
AudioConnection          patchCord9(mixer2, 0, i2s1, 1);
AudioConnection          patchCord10(mixer1, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=523,508
// GUItool: end automatically generated code


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

void setup() {
  Serial.begin(9600);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  for (int i = 0; i < 4; i++) {
    mixer1.gain(i, 0.5);
    mixer2.gain(i, 0.5);
  }

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.


  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  //while (playSdWav1.isPlaying()) {
  // uncomment these lines if you audio shield
  // has the optional volume pot soldered
  //float vol = analogRead(15);
  //vol = vol / 1024;
  // sgtl5000_1.volume(vol);
  // }
}


void loop() {
  for(int i = 1; i<10; i++){
    playSdWave1.play(str(i) + ".wav");
    delay(4000);
  }
    playSdWav1.play("9.wav");  // filenames are always uppercase 8.3 format
    delay(5000);


    playSdWav1.play("1.wav");  // filenames are always uppercase 8.3 format
    delay(5000);


    playSdWav1.play("3.wav");  // filenames are always uppercase 8.3 format
    delay(5000);


    playSdWav1.play("5.wav");  // filenames are always uppercase 8.3 format
    delay(5000);

  /* playFile("2.wav");
    delay(2000);
    playFile("3.wav");
    delay(2000);
    playFile("4.wav");
    delay(2000); */
}

