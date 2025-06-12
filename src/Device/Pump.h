#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Device.h"

class Pump : public Device {
  private:
    unsigned long startTime = 0;
    int pin;

  public:
    Pump(int pumpPin, int manualButtonPin, int statusLedPin);

    void init() override;
    void update() override;
    void on(const char* initiator) override;
    void off(const char* initiator) override;
    void toggle(const char* initiator) override;
    JsonDocument getJsonData() const override;

    void emergencyStop();
    
    bool isRunningTooLong() const;
};

#endif
