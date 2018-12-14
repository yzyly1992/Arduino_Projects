/* HC_SR04
   Paul Badger 2016-revised 2018
   Code for inexpensive sonar sensor
   Warning: You get what you pay for!
   Valley filter eliminates a lot of glitches
   Set up into two functions that you can paste
   into your sketch.
*/

void setup() {
  Serial.begin (9600);

}

void loop() {
  readSensor();
}

unsigned int readSensor() {
#define DUBUG_HC_SRO4 // comment out to get rid of debug printing

  const int trigPin = 17;  // change to the microController pin you are using
  const int echoPin = 16;  // change to the microController pin you are using
  const unsigned int maxDuration = 10000; // around 5 feet - increase if you are trying to sense further
  //                                       // this sensor will not sense people reliably(soft clothing) at
  //                                       // distance past a few feet though
  //                                       // the sensor gets flaky at greater distances.
  const unsigned int readDelay = 50;   // datasheets recommend not reading more often than 50 mS
  //                        // this lets echoes die down from last read
  const unsigned int speed_of_sound_uS_CM = 29;     // speed of sound microseconds per centimeter
  unsigned int duration;
  static unsigned int lastDuration;
  static unsigned int distance_CM, filteredOutput;
  static unsigned int lastRead;     // use long instead of int for Arduino board
  static bool initialized = false;  // flag to set pinMode for pins


  if (!initialized) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    initialized = true;
  }

  if (millis() - lastRead > readDelay) {  // datasheet says don't read oftener than 50 mS

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(200);  // wait as long as possible for transmit transducer to stop ringing
    // before looking for a return pulse
    // if you get zeros in your output reduce 250 by a little, say 200
    duration = pulseIn(echoPin, HIGH, maxDuration);
    // third parameter is the timeout - the sensor
    // has a really long timeout that can slow down your
    // loop significantly if sensor doesn't find an echo
    if (duration == 0) duration = maxDuration;  // eliminate zero if sensor times out

    distance_CM = (duration / 2) / speed_of_sound_uS_CM;
    // for inches change divide distance_CM by 2.54

     filteredOutput = valleyFilter(distance_CM);

    /* TODO - there seems to be an occaisional "runt pulse" ie false output       
     *  that happens just after the sensor times out by the pulseIn() function
     *  Probably it's the sensor but possibly the pulseIn function?
     *  Maybe try to filter this out?
    */

#ifdef DUBUG_HC_SRO4          // uncomment #define above to debug
    Serial.print(duration);
    Serial.print("\t"); // print tab
    Serial.print(distance_CM);
    Serial.print("\t"); // print tab
    Serial.println(filteredOutput);   // noise filter uses raw duration val, return CM
#endif

    lastRead = millis();
  }

  // return distance_CM;  // uncomment for raw values
  return filteredOutput;  // to use the valleyFilter - highly recommended
}

unsigned int valleyFilter(int distance_CM) {
  /* saves the minimum (ie closest) value returned by the sensor for a length of time set below */
  const unsigned int TIME_CONSTANT_MS = 750;      // total time in which to find peak
  const unsigned int SAMPLES_INTERVAL_MS = 100;   // how often to record peaks
  const unsigned int MAX_SAMPLES = (TIME_CONSTANT_MS / SAMPLES_INTERVAL_MS) + 1;

  // these variables all need to be remembered between function calls
  // hence we need to declare them static
  static unsigned int samples[MAX_SAMPLES + 1];
  static unsigned int valley = 65000;
  static unsigned int returnValley;
  static unsigned int lastTime;
  static unsigned int index = 0;


  if (distance_CM < valley) { // if true we found a new valley
    valley = distance_CM;     // store the value in valley variable
  }

  if (millis() - lastTime > SAMPLES_INTERVAL_MS) {
    index = (index + 1) % MAX_SAMPLES; // modulo makes index roll over back to 0 after max
    samples[index] = valley;

    returnValley = 65000; // set variable to a large number since we are looking for minimums
    // now find the valley in the array
    for (int i = 0; i < MAX_SAMPLES; i++) {  // index through the array looking for new minimums
      if (samples[i] < returnValley) { // if true we found a new valley
        returnValley = samples[i];
      }
    }
    valley = 65000;
    lastTime = millis(); // update lastTime for timer
  }

  return returnValley;
}

 
