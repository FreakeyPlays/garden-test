#include "TemperatureSensor.h"
#include "../Config.h"

TemperatureSensor::TemperatureSensor(int sensorPin)
    : pin(sensorPin),
      temperatureCelsius(0.0f),
      lastMeasureTime(0),
      oneWire(sensorPin),
      sensors(&oneWire) {
}

void TemperatureSensor::init() {
    sensors.begin();
}

void TemperatureSensor::update() {
    if((millis() - lastMeasureTime) >= MEASURE_INTERVAL) {
        sensors.requestTemperatures();
        temperatureCelsius = sensors.getTempCByIndex(0);
    }
}

SensorData TemperatureSensor::getData() const {
    return SensorData("temperature", temperatureCelsius, "C");
}

JsonDocument TemperatureSensor::getJsonData() const {
    JsonDocument doc;
    doc["type"] = "temperature";
    doc["value"] = temperatureCelsius;
    doc["unit"] = "C";
    return doc;
}