/* PitchShift
 * Deomonstrates how to use a potentiometer to change the frequency of a melody
 * Paul Badger 2010
 * Uses the frequout function and example sketch as a melody
*/


const int outpin = 10;      // speaker on pin 12
const int potPin1 = A0;       // potentiometer on analog 0
const int potPin2 = A1;
int mapVal1;
int mapVal2;

int  dur;
float noteval;

// note values for two octave scale
// divide them by powers of two to generate other octaves
float A     = 14080;
float AS    = 14917.2;
float B     = 15804.3;
float C     = 16744;
float CS    = 17739.7;
float D     = 18794.5;
float DS    = 19912.1;
float E     = 21096.2;
float F     = 22350.6;
float FS    = 23679.6;
float G     = 25087.7;
float GS    = 26579.5;
float Z2    = 28160;
float Z2S   = 29834.5;
float B2    = 31608.5;
float C2    = 33488.1;
float C2S   = 35479.4;
float D2    = 37589.1;
float D2S   = 39824.3;
float E2    = 42192.3;
float F2    = 44701.2;
float F2S   = 47359.3;
float G2    = 50175.4;
float G2S   = 53159;
float Z3    = 56320;

//octaves  - corresponds to piano octaves
float oct8 = 4;
float oct7 = 8;
float oct6 = 16;
float oct5 = 32;
float oct4 = 64;
float oct3 = 128;
float oct2 = 256;
float oct1 = 512;
float oct0 = 1024;

//rhythm values
int wh = 1024;   // whole note
int h  = 512;    // half note
int dq = 448;    // dotted quarter
int q = 256;     // quarter
int qt = 170;    // quarter note triplet
int de = 192;    // dotted eighth
int e = 128;     // eighth
int et = 85;     // eighth note triplet
int dsx = 96;    // dotted sixteenth
int sx = 64;     // sixteenth
int thx = 32;    // thirty second

// note that rhythm values follow pitch (note) values, be sure to include both pitch and rhythm for new entries
float melody[] = {
    C, dq,   D, e,   E, dq,  F, e,   G, h,   C2, h,   Z2, h,   C2, h,   G, wh,   F, h,   F, dq,
    G, e,   E, h,   E, h,   D, dq,   D, q,   E, e,   C, wh };


void setup() { 
    Serial.println(" running setup ");
    Serial.begin(9600);
} 


void loop(){ 

    // step through melody note by note by stepping through melody ARRAY

    for(int i= 0; i < sizeof(melody) / 4; i = i + 2){     // sizeof() measures the array size
                                                          // divide by 8 since floats have 4 bytes and
                                                          // skip the rhythm values
                                                          // try adding to the array - the music still works

         Serial.println(noteval);

        noteval = melody[i] / oct4;                       // divide by desired octave constant 
         Serial.print(noteval);
          Serial.print("    ");

        int potVal = analogRead(potPin);                  // read the potentiometer
        noteval =  (noteval * (float)potVal)  / 256;      // multiply the potVal ratio by the noteval
                                                          // divide by 256 to scale up two octaves -
                                                          // 1023 / 256 = 4  so 4x is max scale up
                                                          // scaling down is not limited  
                                                          // potVal can be 0 divided by 256
                                                          // bass sound with square waves are nasty though   
        dur = melody[i + 1];


        freqout((int)noteval, dur);
        delay(10);
    }
    delay(500);
}


void freqout(float freq, int t)  // freq in hz, t in ms
{
    int hperiod;                               //calculate 1/2 period in us
    long cycles, i;
    pinMode(outpin, OUTPUT);                   // turn on output pin

    hperiod = (500000.0 / freq) ;             // subtract 7 us to make up for digitalWrite overhead

    cycles = (freq * (float)t) / 1000.0;       // calculate cycles divide by 1000 to convert from milliseconds
    //Serial.print(freq);
    //Serial.print((char)9);                     // ascii 9 is tab - you have to coerce it to a char to work 
    //Serial.print(hperiod);
    //Serial.print((char)9);
    //Serial.println(cycles);

    constrain(hperiod, 1, 16382);              // fix bug in delayMicroseconds

    for (int i=0; i<= cycles; i++){            // play note for t ms 
        digitalWrite(outpin, HIGH); 
        delayMicroseconds(hperiod);
        digitalWrite(outpin, LOW); 
        delayMicroseconds(hperiod - 1);        // - 1 to make up for digitaWrite overhead
    }
    pinMode(outpin, INPUT);                    // shut off pin to avoid noise from other operations

}
