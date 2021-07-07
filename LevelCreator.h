#ifndef LevelCreator_h
#define LevelCreator_h

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 20
#define DELAYVAL 500

class LevelCreator {
    public:
    LevelCreator(int LEDPin): LEDPin(LEDPin){
      pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPin, NEO_GRB + NEO_KHZ800);
      pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED);
    }

    void newFrame(String levelString) {
      const int arraySize = levelString.length();
      int levelArray[arraySize] = {0};
      stringIntoArray(levelString, levelArray);

      drawLed(levelArray, arraySize);

      for(int i = 0; i < arraySize; i++){
        Serial.print(levelArray[i]);
      } 
      Serial.println();
      
    }

    

    private:
    int LEDPin;
    Adafruit_NeoPixel pixels;

    void stringIntoArray(String arrayString, int* resultArray) {
      for(int i = 0; i < arrayString.length(); i++){
        resultArray[i] = arrayString[i] - '0';
      }
    }

     void drawLed(int* level, int levelSize){
      pixels.clear();
      for(int i=0; i<levelSize; i++) { // For each pixel...
        if(level[i]== 0) {
            pixels.setPixelColor(i, pixels.Color(0, 150, 0));
        }else if(level[i] == 1) {
          pixels.setPixelColor(i, pixels.Color(150, 0, 0));
        }
      }
       pixels.show();   // Send the updated pixel colors to the hardware.
    }


    
    
};

#endif
