#ifndef Player_h
#define Player_h

#include "MyServo.h"
#include "MovementState.h"
#include <Arduino.h>

MovementState ground(90, 0, nullptr);
MovementState jump2(45, 1, &ground);
MovementState jump1(45, 1, &jump2);


class Player {
  public:
    Player(MyServo* servo):servo(servo) {
    }

    void newFrame() {
        if(nextState != nullptr) {
            currentState = nextState;
            servo->setPosition(currentState->getTargetPosition());
            nextState = nextState -> getNextState();
        }
    }

    bool jump(){
        if(nextState == nullptr) {
          nextState = &jump1;
          servo->setPosition(nextState->getTargetPosition());
          return true;
        }
        return false;
    }

    void reset() {
      currentState = &ground;
      nextState = nullptr;
      servo->setPosition(ground.getTargetPosition());
    }

    MovementState getMovementState(){
      return *currentState;
    }

  private:
  MyServo* servo;
  MovementState* nextState = nullptr;
  MovementState* currentState = &ground;
};

#endif
