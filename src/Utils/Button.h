#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
  private:
    uint8_t pin;
    bool lastState = HIGH;
    bool currentState = HIGH;
    bool pressedFlag = false;

  public:
    Button(uint8_t pin);

    void init();
    void update();
    bool wasPressed();
};

#endif
