// this program won't work correctly. Still needs frequency to be calculated correctly based off of received coords
// also needs something to switch dirPin, we don't know center coords yet tho, so I couldn't implement this
// love you

#include <SoftwareSerial.h>

String coords = "";
int x = 0;
int y = 0;
int xFreq = 0;
uint8_t yFreq = 0;

void setup() {
   // Timer1 - prescaler 8
  TCCR1A = (1 << COM1A0);
  TCCR1B = (1 << WGM12) | (1 << CS11);
  OCR1A = (F_CPU / (2 * 8 * 1000)) - 1;
  
  // Timer2 - prescaler 64
  TCCR2A = (1 << COM2A0) | (1 << WGM21);
  TCCR2B = (1 << CS22);
  OCR2A = (uint8_t)((F_CPU / (2UL * 64UL * 1000UL)) - 1); // you wouldn't believe how stupid this integer overflow fix is

  int yPulsePin = 8;
  int yDirPin = 9;
  int xPulsePin = 10;
  int xDirPin = 11;

  pinMode(yPulsePin, OUTPUT);
  pinMode(yDirPin, OUTPUT);  // High is pitch up
  pinMode(xPulsePin);
  pinMode(xDirPin, OUTPUT);  // High is counter-clockwise, left


  SoftwareSerial rpiCoords(2, 3);
  rpiCoords.begin(115200);
}

// Function prototypes
void stopTimer1();
void startTimer1();
void stopTimer2();
void startTimer2();
void setxFreq(int xFreq);
void setyFreq(int yFreq);
int frequency_calculator(int coord, int curr_freq);

void loop() {
  static unsigned long lastUpdate = 0;
  while (rpiCoords.available() > 0) {  // receiving coords
    char c = rpiCoords.read();
    if (c == '\n') {  // if we received full coords
      // parse coords
      int commaIndex = coords.indexOf(',');
      x = coords.substring(0, commaIndex).toInt();
      y = coords.substring(commaIndex + 1).toInt();
      // change frequency with parsed coords
      xFreq = frequency_calculator(x, xFreq);
      yFreq = frequency_calculator(y, yFreq);
      setxFreq(xFreq);
      setYFreq(yFreq);
    } else coords += c;
  }
  // timer frequencies cannot not go lower than 122Hz or higher than 1MHz
  // Tim2 OCR2A caps out at 255

  // our turret will be restricted to steps of 10ms (100Hz, but we can't go lower than 122Hz) and 0.5ms (2kHz) 

  // will change frequency and dir with pid based on aforementioned coords
}


void stopTimer1() {
  TCCR1A &= ~(1 << COM1A0);  // Disconnect OC1A
  digitalWrite(xPulsePin, LOW);      // Set pin low
}

void startTimer1() {
  TCCR1A |= (1 << COM1A0);   // Reconnect OC1A to timer
}

void stopTimer2() {
  TCCR2A &= ~(1 << COM2A0);  // Disconnect OC2A
  digitalWrite(yPulsePin, LOW);     // Set pin low
}

void startTimer2() {
  TCCR2A |= (1 << COM2A0);   // Reconnect OC2A to timer
}

void setxFreq(int xFreq) {
  OCR1A = (F_CPU / (2 * 8 * xFreq)) - 1;
}

void setyFreq(int yFreq) {
  OCR2A = (uint8_t)((F_CPU / (2UL * 64UL * (unsigned long)yFreq)) - 1);
}

int frequency_calculator(int coord, int curr_freq) {
  // will return a freq as a function of how far away the target is
  // order of if subject to change. should be:
  //    descending in order of most frequent case

  // this function can also change dirPin without any repercussions
  
  if (curr_freq > 10*coord) {  // if approaching target too fast, slow down. speed is function of how far away target is
    return 10*coord  // add lower bound
  } else if (curr_freq == 0) {  // if stopped, start slow, don't jerk.
    return 1000
  } else if (coord < 20) {  // if close enough to target, stop
    return 0
  } else if (curr_freq < 10*coord) {  // if approaching target and still accelerating, continue to accelerate
    return curr_freq*2  // add upper bound.
  }

  // all hardcoded values subject to change. Just an example for now.
}

