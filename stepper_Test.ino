// Define the stepper motor connections
const int dirPin = A13;
const int stepPin = 4;
const int enablePin =5;

void setup() {
  // Set up the motor control pins as outputs
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Disable the motor by default (active low)
  digitalWrite(enablePin, HIGH);
}

void loop() {
  // Enable the motor
  digitalWrite(enablePin, LOW);

  // Set the direction (1 for clockwise, 0 for counterclockwise)
  digitalWrite(dirPin, HIGH);

  // Step the motor 200 steps
  for (int i = 0; i < 390; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(50000);  // Adjust this delay based on your motor's specifications
    digitalWrite(stepPin, LOW);
    delayMicroseconds(50000);  // Adjust this delay based on your motor's specifications
  }

  // Pause for a moment
  delay(1000);

  // Set the direction opposite for counterclockwise rotation
  digitalWrite(dirPin, LOW);

  // Step the motor 200 steps in the opposite direction
  for (int i = 0; i < 390; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(50000);  // Adjust this delay based on your motor's specifications
    digitalWrite(stepPin, LOW);
    delayMicroseconds(50000);  // Adjust this delay based on your motor's specifications
  }

  // Pause for a moment
  delay(1000);

  // Disable the motor
  digitalWrite(enablePin, HIGH);

  // Pause before the next iteration
  delay(1000);
}
