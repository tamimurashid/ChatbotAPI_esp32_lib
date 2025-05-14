#include "ChatbotAPI.h"

// Define the empty constructor
ChatbotAPI::ChatbotAPI() {
    // No action required
}

void ChatbotAPI::begin(String id, String token) {
    device_id = id;
    auth_token = token;
}

String ChatbotAPI::updateData(String pin, String value) {
    HTTPClient http;
    http.begin("http://192.168.10.103:5000/api/device/update");
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> jsonDoc;  // You can still use StaticJsonDocument as it's safer on embedded
    jsonDoc["device_id"] = device_id;
    jsonDoc["auth_token"] = auth_token;
    jsonDoc["virtualPin"] = pin;
    jsonDoc["value"] = value;

    String requestBody;
    serializeJson(jsonDoc, requestBody);

    int httpResponseCode = http.POST(requestBody);
    String payload = http.getString();

    http.end();
    return payload;
}
