 #include "MyServo.h"
 
 const int PWMFreq = 50;
 const int PWMResolution = 8;
 const int minDutyCyle = 6;
  const int maxDutyCyle = 32;
 MyServo::MyServo(int pin, int channel):channel(channel) {
      ledcSetup(channel, PWMFreq, PWMResolution);
      ledcAttachPin(pin, channel);
    }

void MyServo::update(){
     const int maxStepSize = 10; 
      const int difference = abs(targetPosition - currentPosition);
      const int stepSize = min(maxStepSize, difference);
      if(targetPosition > currentPosition){
           currentPosition += stepSize;
           move(currentPosition);
      } else if (targetPosition < currentPosition) {
           currentPosition -= stepSize;
           move(currentPosition);
      }
}

void  MyServo::setPosition(int position) {
        targetPosition = position;
       update();
  }

void  MyServo::moveSync(int position) {
        targetPosition = position;
         move(position);
        while(currentPosition != targetPosition) {
         update();
        }
  }

int MyServo::move(int angle){
    const int dutyCycle = map(angle, 0, 180, minDutyCyle, maxDutyCyle);
    ledcWrite(channel, dutyCycle);
}
