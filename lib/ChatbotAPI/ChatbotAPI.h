#ifndef CHATBOT_API_H
#define CHATBOT_API_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class ChatbotAPI {
private:
    String device_id;
    String auth_token;

public:
    ChatbotAPI();                  // Only declaration here
    void begin(String id, String token);     // Only declaration here
    String updateData(String pin, String value);  // Only declaration here
};

#endif
