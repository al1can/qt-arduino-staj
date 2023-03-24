#include <AccelStepper.h>

// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
//const int stepsPerRevolution = 200;
#define motorInterfaceType 1

AccelStepper stepper(motorInterfaceType, stepPin, dirPin);

int inChar;
int value;
String inString;

void setup()
{
  Serial.begin(115200);
  
  // Declare pins as Outputs
  //pinMode(stepPin, OUTPUT);
  //pinMode(dirPin, OUTPUT);
  stepper.setMaxSpeed(1000);
}
void loop()
{

  if (Serial.available() > 0) {
    inChar = Serial.read();
    inString += (char)inChar;

    if (inChar == '\n') {
      Serial.print("Value: ");
      Serial.println(inString);

      value = inString.toInt();

      stepper.setSpeed(200);
      stepper.setAcceleration(50);
      stepper.moveTo(value);
      inString = "";
    }
  }
  
  //if (stepper.distanceToGo() == 0)
        //stepper.moveTo(-stepper.currentPosition());

      stepper.run();

}
