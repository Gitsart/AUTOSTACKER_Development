#include <Pixy2.h>
#include <MobaTools.h>

const byte stepPin = 22;
const byte dirPin = 24;
const int stepsPerRev = 400;
const long targetPos = 1600;

MoToStepper myStepper(stepsPerRev, STEPDIR);
MoToTimer stepperPause;
bool stepperRunning;
bool movingForward;
bool signatureDetected;  // Track whether signature 1 is currently detected

Pixy2 pixy;

void setup()
{
  myStepper.attach(stepPin, dirPin);
  myStepper.setSpeed(800);
  myStepper.setRampLen(20);
  stepperRunning = false;
  movingForward = true; // Start by moving forward
  signatureDetected = false;
  Serial.begin(115200);
  Serial.println("Starting...");

  pixy.init();
}

void loop()
{
  // grab blocks!
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

void motor()
{
  if (!stepperRunning && !signatureDetected)
  {
    // Set the flag to true when signature is not detected
    signatureDetected = true;

    // Move forward
    myStepper.move(targetPos);
    Serial.println("Moving forward");
    stepperRunning = true;

    while (myStepper.moving())
    {
      delay(10); // Wait until the forward movement is complete
    }

    // Move backward
    myStepper.move(-targetPos);
    Serial.println("Moving backward");
  
    while (myStepper.moving())
    {
      delay(10); // Wait until the backward movement is complete
    }

    stepperRunning = false; // Reset the flag when the complete oscillation is done
  }
}
