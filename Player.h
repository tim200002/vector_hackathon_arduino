#ifndef Player_h
#define Player_h

#include "MyServo.h"
#include "MovementState.h"
#include <Arduino.h>

MovementState ground(90, 0, nullptr);
MovementState jump3(180, 1, &ground);
MovementState jump2(180, 1, &jump3);
MovementState jump1(180,0, &jump2);





class Player {
  public:
    Player(MyServo* servo, int jumpButton):servo(servo), jumpButton(jumpButton) {
        pinMode(jumpButton, INPUT_PULLUP);
    }

    void newFrame() {
        if(nextState != nullptr) {
            currentState = nextState;
            servo->setPosition(currentState->getTargetPosition());
            nextState = nextState -> getNextState();
        }
    }
    
    void read(){
        const bool jumpButtonLevel = digitalRead(jumpButton);
        if(jumpButtonLevel == LOW && nextState == nullptr) {
          Serial.println("jump");
          nextState = &jump1;
          servo->setPosition(nextState->getTargetPosition());
        }
    }

    MovementState getMovementState(){
      return *currentState;
    }

  private:
  MyServo* servo;
  int jumpButton;
  MovementState* nextState = nullptr;
  MovementState* currentState = &ground;
};

#endif
