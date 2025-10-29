const int step1out = 8;
const int dir1out  = 9;
const int step2out = 10;
const int dir2out  = 11;

const int stepsPerTest = 200; // numstpes
const int slowDelayMs = 100; // RPM/delay (100 max)

void setup() {
  pinMode(step1out, OUTPUT);
  pinMode(dir1out, OUTPUT);
  pinMode(step2out, OUTPUT);
  pinMode(dir2out, OUTPUT);


  // Initialize outputs
  digitalWrite(step1out, HIGH);
  digitalWrite(step2out, HIGH);
  digitalWrite(dir1out, HIGH);  // forward
  digitalWrite(dir2out, HIGH);

  delay(500);
}

void loop() {

  
  digitalWrite(dir1out, HIGH);
  doSteps(stepsPerTest);
  delay(1000);
  digitalWrite(dir1out, LOW);
  doSteps(stepsPerTest);

  delay(3000);
}

void doSteps(int steps) {
  for (int i=0; i<steps; ++i) {
    digitalWrite(step1out, LOW);
    //digitalWrite(step2out, LOW);
    delayMicroseconds(slowDelayMs);
    digitalWrite(step1out, HIGH);
    //digitalWrite(step2out, HIGH);
    delayMicroseconds(slowDelayMs);
  }
}
