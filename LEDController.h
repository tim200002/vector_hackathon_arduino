#ifndef LEDController_h
#define LEDController_h

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 20

class LEDController {
    public:
    LEDController(int LEDPin): LEDPin(LEDPin){
      pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPin, NEO_GRB + NEO_KHZ800);
      pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED);
    }

     void drawNewFrame(int* level, int levelSize){
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

    void drawSolidColor(int red, int green, int blue) {
      pixels.clear();
      for(int i = 0; i < NUMPIXELS; ++i){
        pixels.setPixelColor(i, pixels.Color(red, green, blue));
      }
       pixels.show(); 
    }

    void blinkSolidColor(int red, int green, int blue) {
      drawSolidColor(red, green, blue);
      delay(300);
      pixels.clear();
      pixels.show();
      delay(300);
      drawSolidColor(red, green, blue);
      delay(300);
      pixels.clear();
      pixels.show();
    }
    

    private:
    int LEDPin;
    Adafruit_NeoPixel pixels; 
};

#endif
