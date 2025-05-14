#include "ChatbotAPI.h"

ChatbotAPI::ChatbotAPI(String url) {
    base_url = url;
}

void ChatbotAPI::begin(String id, String token) {
    device_id = id;
    auth_token = token;
}

String ChatbotAPI::updateData(String pin, String value) {
    HTTPClient http;
    http.begin(base_url + "/api/device/update");
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> jsonDoc;
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
