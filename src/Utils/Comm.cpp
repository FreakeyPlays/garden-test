#include "Comm.h"
#include "../Events.h"

Comm& Comm::getInstance() {
    static Comm instance;
    return instance;
}

void Comm::init(unsigned long baudRate) {
    Serial.begin(baudRate);
    while (!Serial);
}

void Comm::send(const char* msg) {
    JsonDocument doc;
    doc["type"] = "log";
    doc["message"] = msg;
    serializeJson(doc, Serial);
    Serial.println();
}

void Comm::sendEvent(const char* event, const char* initiator) {
    JsonDocument doc;
    doc["type"] = "event";
    doc["eventId"] = event;
    doc["message"] = Event::getMessage(event);
    doc["initiator"] = initiator;
    doc["timestamp"] = millis();
    serializeJson(doc, Serial);
    Serial.println();
}

void Comm::sendData(JsonDocument doc) {
    JsonDocument messageDoc;

    messageDoc["type"] = "data";
    messageDoc["timestamp"] = millis();

    JsonObject plantObj = messageDoc.createNestedObject("plant");
    plantObj.set(doc.as<JsonObject>());

    serializeJson(messageDoc, Serial);
    Serial.println();
}
