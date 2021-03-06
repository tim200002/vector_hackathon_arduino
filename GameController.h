#ifndef GameController_h
#define GameController_h

#include "Player.h"
#include "LevelCreator.h"
#include "SoundController.h"
#include <MQTT.h>



#define playerId "2"
#define jumpButton 32

// possible states are Ready, Running, Stopped

class GameController {
  public:
    GameController(Player* player,LevelCreator* levelCreator, LEDController* ledController, MQTTClient* mqttClient, SoundController* soundController):player(player), levelCreator(levelCreator), ledController(ledController), mqttClient(mqttClient),soundController(soundController){
        pinMode(jumpButton, INPUT_PULLUP);
      }

    void startupSequence(){
      ledController -> blinkSolidColor(0,0,255);
      reset();
    }

    void reset(){
      ledController -> drawSolidColor(255,255,255);
      player->reset();
      mqttClient->publish("/LED_Invader/ready", playerId);
      state = "Ready";
    }
    
    void startGame(){
      state = "Running"; 
    }

    void onWinner(String winnerId){
        if(winnerId == playerId) {
            state = "Stopped";
            ledController -> drawSolidColor(0,255,0);
            soundController->playVictory2();
        }
    }

    void onLoser(String looserId){
        if(looserId == playerId) {
          state = "Stopped";
            ledController -> drawSolidColor(255,0,0);
            soundController->playCollision2();
        }
    }

    void newFrame(String frame){
        if(state == "Ready" || state == "Running"){
          state = "Running";
            levelCreator->newFrame(frame);
            player->newFrame();
            if(checkCollision()){
              mqttClient->publish("/LED_Invader/collision", playerId);
            }
        }
    }

    void read(){
        const bool jumpButtonLevel = digitalRead(jumpButton);
        if(jumpButtonLevel == LOW) {
          jumpPressed();
        }
    }

    
  private:
    String state = "undefined";
    Player* player;
    LEDController* ledController;
    LevelCreator* levelCreator;
    MQTTClient* mqttClient;
    SoundController* soundController;

    void jumpPressed(){
      if(state == "Stopped"){
          reset();
      }else if(state == "Running"){
        if(player->jump())
          soundController->playJump();
      }
    }
    bool checkCollision() {
      return levelCreator->valueAtPlayer == 1 && player->getMovementState().getLocation() != 1 ;
    }
};

#endif
