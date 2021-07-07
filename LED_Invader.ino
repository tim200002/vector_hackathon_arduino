#include "MyServo.h"
#include "LevelCreator.h"
#include <MQTT.h>
#include <WiFi.h>

const int buttonPin = 32;
MyServo myServo(25);
LevelCreator myLevelCreator(27);

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
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
   // start wifi and mqtt
  WiFi.begin(ssid, pass);
  client.begin("vectorhackathon21.cloud.shiftr.io", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();

  
  const bool isPressed = digitalRead(buttonPin);
  if(isPressed){
     myServo.setPosition(0);
    }
  else {
       myServo.setPosition(180);
  }
  myServo.update();
   
}
