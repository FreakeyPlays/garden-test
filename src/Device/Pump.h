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
    void on(EventInitiator initiator = EventInitiator::AUTO) override;
    void off(EventInitiator initiator = EventInitiator::AUTO) override;
    void toggle(EventInitiator initiator = EventInitiator::AUTO) override;
    JsonDocument getJsonData() const override;

    void emergencyStop();
    
    bool isRunningTooLong() const;
};

#endif
