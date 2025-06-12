#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
  public:
    Led(int pin);

    void init();
    void on();
    void off();
    void toggle();
    bool isOn() const;

  private:
    int pin;
    bool state;
};

#endif
