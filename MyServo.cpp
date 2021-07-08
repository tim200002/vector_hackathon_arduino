 #include "MyServo.h"
 #include <Arduino.h>
 
 MyServo::MyServo(int pin) {
      myServo.setPeriodHertz(50);    // standard 50 hz servo
      myServo.attach(pin, 600, 2400); // attaches the servo on pin 18 to the servo object
    }

void MyServo::update(){
      const int maxStepSize = 45; 
      const int difference = abs(targetPosition - currentPosition);
      const int stepSize = min(maxStepSize, difference);
      if(targetPosition > currentPosition){
           currentPosition += stepSize;
           myServo.write(currentPosition);
      } else if (targetPosition < currentPosition) {
           currentPosition -= stepSize;
           myServo.write(currentPosition);
      }
}

void  MyServo::setPosition(int position) {
        targetPosition = position;
        update();
  }

void  MyServo::moveSync(int position) {
        targetPosition = position;
        while(currentPosition != targetPosition) {
          update();
        }
  }
