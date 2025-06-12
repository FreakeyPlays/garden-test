#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class MoistureSensor : public Sensor {
    private:
        static constexpr int IN_MIN = 0;
        static constexpr int IN_MAX = 1023;
        static constexpr double OUT_MIN = 0.0;
        static constexpr double OUT_MAX = 100.0;

        int pin;
        float moisturePercent;

        unsigned long lastMeasureTime;
    
        float mapValue(int value) const;
    
    public:
        MoistureSensor(int sensorPin);
        SensorData getData() const override;
        JsonDocument getJsonData() const override;
        void init() override;
        void update() override;
};

#endif