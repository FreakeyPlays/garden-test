#ifndef DEVICE_H
#define DEVICE_H

#include <ArduinoJson.h>
#include "../Utils/Button.h"
#include "../Utils/Led.h"

class Device {
  protected:
    bool isActive = false;
    Button manualToggle;
    Led statusLed;

  public:
    Device(int manualTogglePin, int statusLedPin)
      : manualToggle(manualTogglePin), statusLed(statusLedPin) {}
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void on(const char* initiator) = 0;
    virtual void off(const char* initiator) = 0;
    virtual void toggle(const char* initiator) = 0;
    virtual JsonDocument getJsonData() const = 0;

    bool getIsActive() const {
      return isActive;
    }
};

#endif
