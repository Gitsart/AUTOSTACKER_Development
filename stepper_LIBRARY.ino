#include<MobaTools.h>
const byte stepPin = 18;
const byte dirPin =17;
const byte cloth = 5;
int detect =0;
bool stepperRunning;
MoToTimer stepperPause;

long  nextPos;
const long targetPos =2800;

const int stepsperRev = 1000;

MoToStepper stepper1(stepsperRev, STEPDIR);
void setup() {
  stepper1.attach(stepPin,dirPin);
  stepper1.setRampLen(stepsperRev/10);
    stepper1.setSpeed(3000);
    pinMode(cloth,INPUT_PULLUP);
    Serial.begin(9600);
    
  
  
}

void loop() {

  detect = digitalRead(cloth);
  Serial.print("C");Serial.println(detect);
  if(detect==0){
    motor();
  }else{
    Serial.println("NO CLOTH");
  }
}
void motor() {

  if ( stepperRunning ) {
    // Wait till stepper has reached target, then set pause time
    if ( !stepper1.moving() ) {
      // stepper has reached target, start pause
      stepperPause.setTime( 500 );
      stepperRunning = false;
    }
  } else {
    // stepper doesn't move, wait till stepperPause time expires
    if ( stepperPause.expired() ) {
      // stepperPause time expired. Start stepper in opposite direction
      if ( nextPos == 800 ) {
        nextPos = targetPos;
      } else {
        nextPos = 800;
      }
      stepper1.moveTo(-nextPos );
      stepperRunning = true;
    }
  }
}
