#ifndef LevelCreator_h
#define LevelCreator_h

#include "LEDController.h"

#define playerPosition 3

class LevelCreator {
    public:
    LevelCreator(LEDController* ledController): ledController(ledController){
    }

    void newFrame(String levelString) {
      const int arraySize = levelString.length();
      int levelArray[arraySize] = {0};
      stringIntoArray(levelString, levelArray);

      valueAtPlayer = levelArray[playerPosition];

      ledController -> drawNewFrame(levelArray, arraySize);
    }

    int valueAtPlayer = 0;

    private:
    LEDController* ledController;

    void stringIntoArray(String arrayString, int* resultArray) {
      for(int i = 0; i < arrayString.length(); i++){
        resultArray[i] = arrayString[i] - '0';
      }
    }   
};

#endif
