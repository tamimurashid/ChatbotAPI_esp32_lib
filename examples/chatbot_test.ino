#include <Arduino.h>
#include <WiFi.h>
#include <ChatbotAPI.h>

const char* device_id = "Smart_device_9343e135";
const char* auth_token = "ba689c446d67cc99c68e60478392a59b";

const char* ssid = "Reindeer";
const char* password = "200120022003";

ChatbotAPI chatbot;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  chatbot.begin(device_id, auth_token);
}

void loop() {
  String response = chatbot.updateData("V1", "30");
  Serial.println("Server reply: " + response);

  delay(1000);
}
