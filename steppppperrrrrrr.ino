const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;
const int homeSwitchPin = 9; // Connect a home position switch to this pin

int stepCount = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW); // Motor active
  pinMode(homeSwitchPin, INPUT_PULLUP); // Home position switch with pull-up resistor

  Serial.begin(9600);
  Serial.print("START");

  homing();// Run homing routine to set the home position
}

void loop() {

  // Your main code logic goes here
  // For example, rotate the motor clockwise for 360 steps
  rotateClockwise(50);
  delay(1000);

  // Rotate the motor counterclockwise for 360 steps
  rotateCounterClockwise(50);
  delay(1000);
  
  rotateClockwise(150);
  delay(1000);

  // Rotate the motor counterclockwise for 360 steps
  rotateCounterClockwise(150);
  delay(1000);

  rotateClockwise(250);
  delay(1000);

  // Rotate the motor counterclockwise for 360 steps
  rotateCounterClockwise(250);
  delay(1000);

  rotateClockwise(350);
  delay(1000);

  // Rotate the motor counterclockwise for 360 steps
  rotateCounterClockwise(350);
  delay(1000);
}

void rotateClockwise(int numSteps) {
  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  for (int x = 0; x < numSteps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10000);
    stepCount++;
    Serial.print("Clockwise:");
    Serial.println(stepCount);
  }
}

void rotateCounterClockwise(int numSteps) {
  digitalWrite(dirPin, LOW); // Changes the direction of rotation
  for (int x = 0; x < numSteps; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10000);
    stepCount--;
    Serial.print("CounterClockwise:");
    Serial.println(stepCount);
  }
}

void homing() {
  // Move the motor until the home switch is pressed
  while (digitalRead(homeSwitchPin) == HIGH) {
    hom_fwd();
    if(stepCount < -500){hom_rev();}
    else if(stepCount > 500) {stOp();}
  }

  // Set the step count to 0 after homing
  stepCount = 0;

  // Move the motor a few steps in the clockwise direction to settle at the home position
  rotateClockwise(10);
}

void hom_rev() {
    digitalWrite(dirPin, HIGH); // Move in the clockwise direction during homing
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10000);
    stepCount++;
}

void hom_fwd() { 
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10000);
    stepCount--;}

void stOp() {
  digitalWrite(enPin,HIGH);
  Serial.println("ERROR,RESTART");
}
