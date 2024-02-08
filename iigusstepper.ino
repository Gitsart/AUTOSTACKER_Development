#include<MobaTools.h>
const byte stepPin = 22;
const byte dirPin =24;

const int stepsperRev = 200;
const int sPeed = 1000;

int count =0;


MoToStepper stepper1(stepsperRev, STEPDIR);
void setup() {
  Serial.begin(9600);
  stepper1.attach(stepPin,dirPin);
  stepper1.setRampLen();
  stepper1.setZero();  
}


void loop() {
  motor();
  
  
}

void motor() {
  stepper1.setSpeed(1000);
  stepper1.rotate(1);
  count++;
  Serial.print(count);
  Serial.println("Forward");
  delay(2000);
  stepper1.stop();
  stepper1.rotate(-1);
  count--;
  Serial.print(count);
  Serial.println("Reverse");
  delay(2000);
}
