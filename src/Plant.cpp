#include "Plant.h"
#include "Events.h"
#include "Utils/Comm.h"

int Plant::nextId = 0;

Plant::Plant() {
    id = nextId++;
}


void Plant::update() {
    for (int i = 0; i < sensorCount; i++) {
        sensors[i]->update();
    }

    for (int i = 0; i < deviceCount; i++) {
        devices[i]->update();
    }

    lastChecked = millis();
}

void Plant::init() {
    for (int i = 0; i < sensorCount; i++) {
        sensors[i]->init();
    }

    for (int i = 0; i < deviceCount; i++) {
        devices[i]->init();
    }
}

JsonDocument Plant::getJsonData() const {
    JsonDocument doc;

    doc["id"] = id;
    doc["lastChecked"] = lastChecked;
    doc["targetMoisture"] = targetMoisture;
    doc["targetTemp"] = targetTemp;

    JsonArray sensorsArray = doc["sensors"].to<JsonArray>();
    for (int i = 0; i < sensorCount; i++) {
        JsonDocument sensorDoc = sensors[i]->getJsonData();

        JsonObject sensor = sensorsArray.add<JsonObject>();
        sensor["type"] = sensorDoc["type"];
        sensor["value"] = sensorDoc["value"];
        sensor["unit"] = sensorDoc["unit"];
    }

    JsonArray devicesArray = doc["devices"].to<JsonArray>();
    for (int i = 0; i < deviceCount; i++) {
        JsonDocument sensorDoc = devices[i]->getJsonData();

        JsonObject device = devicesArray.add<JsonObject>();
        device["type"] = sensorDoc["type"];
        device["isActive"] = sensorDoc["isActive"];
    }

    return doc;
}

void Plant::addSensor(Sensor* sensor) {
    if (sensorCount < 2) {
        sensors[sensorCount++] = sensor;
    }
}

void Plant::addDevice(Device* device) {
    if (deviceCount < 1) {
        devices[deviceCount++] = device;
    }
}

void Plant::executeCommand(const JsonDocument& doc) {
    const char* command = doc["command"];

    if(strcmp(command, Event::PUMP_ON) == 0) {
        devices[0]->on(EventInitiator::REMOTE);
    } else if (strcmp(command, Event::PUMP_OFF) == 0) {
        devices[0]->off(EventInitiator::REMOTE);
    } else {
        COMM.send("Unknown Plant command!");
    }
}