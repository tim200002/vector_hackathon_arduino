#ifndef MyServo_h
#define MyServo_h

#include <ESP32Servo.h>
#include "Arduino.h"

class MyServo {
   public:
    MyServo(int pin);
    void setPosition(int position);
    void moveSync(int position);
    void update();
  private:
    int currentPosition = 0;
    int targetPosition = 0;
    Servo myServo;
 
};

#endif
