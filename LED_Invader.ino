#include "MyServo.h"
#include "Player.h"
#include "LevelCreator.h"
#include "GameController.h"
#include "LEDController.h"
#include "SoundController.h"
#include <MQTT.h>
#include <WiFi.h>

WiFiClient net;
MQTTClient client;

LEDController ledController(27);
MyServo playerServo(25, 0);
LevelCreator myLevelCreator(&ledController);
Player player(&playerServo);
SoundController soundController(16, 8);
GameController gameController(&player, &myLevelCreator, &ledController, &client, &soundController);


const char ssid[] = "Haus";            // put your wifi ssid here
const char pass[] = "MoRaiX1X";        // put your wifi pass here
const char device[] = "nameyourdevice";        // put your wifi pass here



void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(device, "vectorhackathon21", "vhagHTBZziU6AJskE")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("LED_Invader/new_frame");
  client.subscribe("LED_Invader/loser");
  client.subscribe("LED_Invader/winner");
}

void messageReceived(String &topic, String &payload) {
  if(topic == "LED_Invader/new_frame"){
    gameController.newFrame(payload);
  } else if(topic == "LED_Invader/loser"){
    gameController.onLoser(payload);
  } else if(topic == "LED_Invader/winner"){
    Serial.println("on winner");
    gameController.onWinner(payload);
  } 
}

void setup() {
  Serial.begin(115200);
  ledController.drawSolidColor(0,0,255);
   // start wifi and mqtt
  WiFi.begin(ssid, pass);
  client.begin("vectorhackathon21.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
  playerServo.moveSync(90);
  gameController.startupSequence();

}

void loop() {
  client.loop();
  playerServo.update();
  soundController.loop();
  gameController.read();
  
}
