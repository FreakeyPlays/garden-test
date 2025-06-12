#include "Button.h"

Button::Button(uint8_t pin) : pin(pin) {}

void Button::init() {
  pinMode(pin, INPUT_PULLUP);
  lastState = digitalRead(pin);
}

void Button::update() {
  currentState = digitalRead(pin);

  if (lastState == HIGH && currentState == LOW) {
    pressedFlag = true;
  }

  lastState = currentState;
}

bool Button::wasPressed() {
  if (pressedFlag) {
    pressedFlag = false;
    return true;
  }
  return false;
}
