#include "Led.h"

Led::Led(int pin) : pin(pin), state(false) {}

void Led::init() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    state = false;
}

void Led::on() {
    digitalWrite(pin, HIGH);
    state = true;
}

void Led::off() {
    digitalWrite(pin, LOW);
    state = false;
}

void Led::toggle() {
    if (state) {
        off();
    } else {
        on();
    }
}

bool Led::isOn() const {
    return state;
}
