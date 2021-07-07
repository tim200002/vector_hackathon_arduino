#include "MyServo.h"
#include "Player.h"
#include "LevelCreator.h"
#include "GameController.h"
#include "LEDController.h"
#include <MQTT.h>
#include <WiFi.h>

WiFiClient net;
MQTTClient client;

LEDController ledController(27);
MyServo playerServo(25);
LevelCreator myLevelCreator(&ledController);
Player player(&playerServo);
GameController gameController(&player, &myLevelCreator, &ledController, &client);


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
}

void messageReceived(String &topic, String &payload) {
  if(topic == "LED_Invader/new_frame"){
    gameController.newFrame(payload);
  } else if(topic == "LED_Invader/loser"){
    gameController.stopGame(payload);
  } 
}

void setup() {
  Serial.begin(115200);
  gameController.startupSequence();
   // start wifi and mqtt
  WiFi.begin(ssid, pass);
  client.begin("vectorhackathon21.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  playerServo.moveSync(90);
  connect();
}

void loop() {
  client.loop();
  gameController.read();
  playerServo.update();
}
