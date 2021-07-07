#ifndef MovementState_h
#define MovementState_h
class MovementState {
    public:
        MovementState(int targetPosition,int location, MovementState* nextState):
            nextState(nextState), targetPosition(targetPosition), location(location){};

        MovementState* getNextState(){
            return nextState;
        }

        int getTargetPosition(){
            return targetPosition;
        }

        int getLocation(){
          return location;
        }


    private:
        int targetPosition;
        MovementState* nextState;
        int location; //-1 low 0 neutral 1 high
};
#endif
