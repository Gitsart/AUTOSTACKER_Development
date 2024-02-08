#include<MobaTools.h>
#include <Pixy2.h>
const byte stepPin = 22;
const byte dirPin =24;
const int stepsperRev = 200;
int signature =0;
int count=0;


MoToStepper stepper1(stepsperRev, STEPDIR);
Pixy2 pixy;

void setup() {
  Serial.begin(115200);
  stepper1.attach(stepPin,dirPin);
  stepper1.setRampLen(stepsperRev/10);
  pixy.init();
}

void loop() {
  int i;
  pixy.ccc.getBlocks();
  Serial.print(signature);
  
  signature = pixy.ccc.blocks[i].m_signature;
  if(signature!=1) {motor();}
  
}

void motor() {
  stepper1.setSpeed(2000);
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
