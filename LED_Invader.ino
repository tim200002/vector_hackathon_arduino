#include "MyServo.h"
#include "Player.h"
#include "LevelCreator.h"
#include "GameController.h"
#include <MQTT.h>
#include <WiFi.h>

MyServo playerServo(25);
LevelCreator myLevelCreator(27);
Player player(&playerServo, 32);
GameController gameController(&player, &myLevelCreator);


const char ssid[] = "Haus";            // put your wifi ssid here
const char pass[] = "MoRaiX1X";        // put your wifi pass here
const char device[] = "nameyourdevice";        // put your wifi pass here

WiFiClient net;
MQTTClient client;

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
}

void messageReceived(String &topic, String &payload) {
  if(topic == "LED_Invader/new_frame")
    myLevelCreator.newFrame(payload);
    player.newFrame();
    Serial.println(gameController.checkCollision());
    
}

void setup() {
  Serial.begin(115200);
   // start wifi and mqtt
  WiFi.begin(ssid, pass);
  client.begin("vectorhackathon21.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  playerServo.moveSync(90);
  connect();
}

void loop() {
  client.loop();
  player.read();
  playerServo.update();
}
