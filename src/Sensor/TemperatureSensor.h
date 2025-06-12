#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include "Sensor.h"
#include "SensorData.h"


class TemperatureSensor : public Sensor {
    private:
        int pin;
        float temperatureCelsius;
        OneWire oneWire;
        DallasTemperature sensors;

        unsigned long lastMeasureTime;
    
    public:
        TemperatureSensor(int sensorPin);
        SensorData getData() const override;
        JsonDocument getJsonData() const override;
        void init() override;
        void update() override;
};

#endif