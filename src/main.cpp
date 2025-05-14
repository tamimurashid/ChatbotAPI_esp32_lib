#include <Arduino.h>
#include <WiFi.h>
#include <ChatbotAPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// WiFi credentials
const char* ssid = "Reindeer";
const char* password = "200120022003";

// Chatbot credentials
const char* device_id = "Smart_device_9343e135";
const char* auth_token = "ba689c446d67cc99c68e60478392a59b";

// Sensor definitions
#define DHTPIN 27
#define DHTTYPE DHT22
#define RAIN_SENSOR_PIN 34
#define SOIL_SENSOR_PIN 35

// Objects
ChatbotAPI chatbot;
LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  // Chatbot init
  chatbot.begin(device_id, auth_token);

  // Sensor & LCD init
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(SOIL_SENSOR_PIN, INPUT);

  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int rainValue = digitalRead(RAIN_SENSOR_PIN);
  int soilValue = digitalRead(SOIL_SENSOR_PIN);

  // Prepare data
  String tempStr = String(temperature, 1) + " C";
  String humidStr = String(humidity, 1) + " %";
  String rainStr = rainValue ? "No Rain" : "Rain";
  String soilStr = soilValue ? "Dry" : "Wet";

  // Send to chatbot server
  String respTemp = chatbot.updateData("V1", tempStr);
  String respHumid = chatbot.updateData("V2", humidStr);
  String respRain = chatbot.updateData("V3", rainStr);
  String respSoil = chatbot.updateData("V4", soilStr);

  // Display on Serial
  Serial.println("Sent Data:");
  Serial.println("Temp: " + tempStr + " | Reply: " + respTemp);
  Serial.println("Humidity: " + humidStr + " | Reply: " + respHumid);
  Serial.println("Rain: " + rainStr + " | Reply: " + respRain);
  Serial.println("Soil: " + soilStr + " | Reply: " + respSoil);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C   ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);
  lcd.print(" %  ");

  lcd.setCursor(0, 2);
  lcd.print("Rain: ");
  lcd.print(rainStr);
  lcd.print("      ");

  lcd.setCursor(0, 3);
  lcd.print("Soil: ");
  lcd.print(soilStr);
  lcd.print("       ");

  delay(10000); // Update every 10 seconds
}
