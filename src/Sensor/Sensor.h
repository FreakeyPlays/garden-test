#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "SensorData.h"

class Sensor {
  private:
    unsigned long lastMeasureTime;

  public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual SensorData getData() const = 0;
    virtual JsonDocument getJsonData() const = 0;
    virtual ~Sensor() {};
};

#endif