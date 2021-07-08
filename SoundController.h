#ifndef SoundController_h
#define SoundController_h

const int channel = 1;
const int buzzerPin = 19;

#include <ESP32Servo.h>

class Tone {
  public:
    Tone(int frequency, int playAt, Tone* next):frequency(frequency), playAt(playAt), next(next){
       ledcAttachPin(buzzerPin, channel);
    };
    int frequency;
    unsigned long playAt;
    Tone* next;
};

class SoundController{
    public:
      SoundController(){}

      void playCollision(){
            cleanup();
            Tone* fourthTone = new Tone(0, millis()+1500, nullptr);          
            Tone* thirdTone = new Tone(400, millis()+1000, fourthTone);
            Tone* secondTone = new Tone(600, millis()+500, thirdTone);
            Tone* firstTone = new Tone(800, millis(), secondTone);

            nextTone = firstTone;
      }
      void playCollision2(){
            cleanup();
            Tone* lastTone = new Tone(0, millis()+500, nullptr);          
            Tone* fithTone = new Tone(800, millis()+400, lastTone);
            Tone* fourthTone = new Tone(850, millis()+300, fithTone);
            Tone* thirdTone = new Tone(900, millis()+200, fourthTone);
            Tone* secondTone = new Tone(950, millis()+100, thirdTone);
            Tone* firstTone = new Tone(1000, millis(), secondTone);

            nextTone = firstTone;
      }

       void playVictory1(){
            cleanup();
            Tone* lastTone = new Tone(0, millis()+500, nullptr);          
            Tone* fithTone = new Tone(400, millis()+400, lastTone);
            Tone* fourthTone = new Tone(450, millis()+300, fithTone);
            Tone* thirdTone = new Tone(500, millis()+200, fourthTone);
            Tone* secondTone = new Tone(450, millis()+100, thirdTone);
            Tone* firstTone = new Tone(400, millis(), secondTone);

            nextTone = firstTone;
      }

      void playVictory2(){
            cleanup();
            Tone* lastTone = new Tone(0, millis()+500, nullptr);          
            Tone* fithTone = new Tone(1000, millis()+400, lastTone);
            Tone* fourthTone = new Tone(950, millis()+300, fithTone);
            Tone* thirdTone = new Tone(900, millis()+200, fourthTone);
            Tone* secondTone = new Tone(850, millis()+100, thirdTone);
            Tone* firstTone = new Tone(800, millis(), secondTone);

            nextTone = firstTone;
      }

       void playJump(){
            cleanup();
            Tone* lastTone = new Tone(0, millis()+100, nullptr);          
            Tone* firstTone = new Tone(800, millis(), lastTone);
            nextTone = firstTone;
      }

      void instantMute(){
         cleanup();
         noTone(buzzerPin);
      }

      void loop(){
          if(nextTone != nullptr){
            Serial.println("Tone");
            if(millis() > nextTone -> playAt){
              playTone();
            }
          }
      }

        
      private:

        Tone* nextTone = nullptr;

       void playTone(){
          if(nextTone -> frequency == 0){
             noTone(buzzerPin);
          }else {
             ledcWriteTone(channel, nextTone -> frequency);
             tone(buzzerPin, nextTone -> frequency);
          }
          const Tone* temp = nextTone;
          nextTone = nextTone-> next;
          // clean up
          delete temp;
       }

       void cleanup(){
        while(nextTone != nullptr){
          const Tone* temp = nextTone;
          nextTone = nextTone->next;
          delete temp;
          }
       }
};
#endif
