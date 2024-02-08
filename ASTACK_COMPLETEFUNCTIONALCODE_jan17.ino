#include<MobaTools.h>
#include <Pixy2.h>

const byte stepPin = 22;
const byte dirPin =24;

#define limitPin 8
#define startPin 11

const int stepsperRev = 200;
const long targetPos = 1600;

int count = 0;
int limit_count =0;

bool limswitch =0;

int hOme =0;
int pos =0;
int sTart =0;

MoToStepper stepper1(stepsperRev, STEPDIR);
MoToTimer stepperPause;
bool stepperRunning;
bool movingForward;
bool signatureDetected;

Pixy2 pixy;


void setup() {
  Serial.begin(115200);
  stepper1.attach(stepPin,dirPin);
  stepper1.setRampLen(stepsperRev/8);
  stepperRunning = false;
  movingForward = true; // Start by moving forward
  signatureDetected = false;

  pinMode(limitPin, INPUT);
  pinMode(startPin, INPUT_PULLUP);


  Serial.println("Starting...");

  pixy.init();
  
  homing();
  set_pos();
}

void loop() {
    while(digitalRead(startPin)==LOW)
    {sTart =1;}

    
    if((hOme ==2)&& (limit_count>0)&&(count ==0)&&(pos=1)&& (sTart ==1))
  {
    pixy.ccc.getBlocks();

  bool foundSignature1 = false;

  for (int i = 0; i < pixy.ccc.numBlocks; i++)
  {
    int signature = pixy.ccc.blocks[i].m_signature;
    Serial.println(signature);

    if (signature == 1)
    {
      foundSignature1 = true;
      Serial.println("Signature 1 found");
      break;
    }
  }

  if (!foundSignature1)
  {
    signatureDetected = false; // Reset the flag when signature is not detected
    motor();
  }
  }
}

void homing() {
  stepper1.setSpeed(800);
  while(digitalRead(limitPin) != LOW && limit_count==0) { stepper1.rotate(-1);Serial.print(limswitch);Serial.println("Finding END");}

  if(digitalRead(limitPin) == LOW && limit_count ==0) {stepper1.stop();Serial.println("END POSITION");limit_count+=1;limswitch=HIGH;hOme =1;}
  Serial.print("limit_count:");Serial.println(limit_count);
  Serial.print("limswitch:");Serial.println(limswitch);
  Serial.print("hOme:");Serial.println(hOme);
  Serial.print("POS:");Serial.println(pos);
  delay(2000);
  stepper1.rotate(1);
  limswitch =LOW;
  delay(1000);
  
  }    //limit_count=1,limswitch=LOW,hOme=1,pos=0

void set_pos() {
  
  if(pos ==0&&(digitalRead(limitPin==1))) { 
    stepper1.setSpeed(400);
    stepper1.rotate(-1);
    delay(2000);
    hOme = hOme+1;
    Serial.print("home2=");
    Serial.println(hOme);
    Serial.print("limswitch=");
    Serial.println(limswitch);
    if(digitalRead(limitPin==0)){stepper1.stop();limswitch=HIGH;}}
  if(hOme ==2 && limit_count >0 && limswitch ==HIGH && pos ==0&&(digitalRead(limitPin==0))){
      stepper1.rotate(1);
      delay(3000);
      pos =1;
      stepper1.rotate(1);delay(1500);stepper1.stop();
      Serial.println("StartPositionSet, READY TO USE");}
} // hOme=2,pos=1,limswitch=HIGH,


void motor() {

  stepper1.setSpeed(2000);
  if (!stepperRunning && !signatureDetected)
  {
    // Set the flag to true when signature is not detected
    signatureDetected = true;

    // Move forward
    stepper1.move(targetPos);
    Serial.println("Moving forward");
    stepperRunning = true;

    while (stepper1.moving())
    {
      delay(10); // Wait until the forward movement is complete
    }

    // Move backward
    stepper1.move(-targetPos);
    Serial.println("Moving backward");

    while (stepper1.moving())
    {
      delay(10); // Wait until the backward movement is complete
    }

    stepperRunning = false; // Reset the flag when the complete oscillation is done
  }
}
