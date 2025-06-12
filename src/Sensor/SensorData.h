#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <Arduino.h>

struct SensorData {
    String type;     // e.g. "moisture", "temperature"
    float value;     // numeric value
    String unit;     // e.g. "%", "C"

    SensorData(const String& t, float v, const String& u)
        : type(t), value(v), unit(u) {}
};

#endif