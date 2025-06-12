#include "MoistureSensor.h"
#include "../Config.h"

MoistureSensor::MoistureSensor(int sensorPin)
    : pin(sensorPin), moisturePercent(0.0f), lastMeasureTime(0) {
}

float MoistureSensor::mapValue(int value) const {
    return (float)(value - IN_MIN) * (OUT_MAX - OUT_MIN) / (IN_MAX - IN_MIN) + OUT_MIN;
}

void MoistureSensor::update() {
    if((millis() - lastMeasureTime) >= MEASURE_INTERVAL) {
        int rawValue = analogRead(pin);
        moisturePercent = mapValue(rawValue);
    }
}

void MoistureSensor::init() {
    //pinMode(pin, INPUT);
}

SensorData MoistureSensor::getData() const {
    return SensorData("moisture", moisturePercent, "%");
}

JsonDocument MoistureSensor::getJsonData() const {
    JsonDocument doc;
    doc["type"] = "moisture";
    doc["value"] = moisturePercent;
    doc["unit"] = "%";
    return doc;
}