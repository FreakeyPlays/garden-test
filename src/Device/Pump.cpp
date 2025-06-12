#include "Pump.h"
#include "../Config.h"
#include "../Events.h"
#include "../Utils/Comm.h"
#include "../System.h"

Pump::Pump(int pumpPin, int manualTogglePin, int statusLedPin) : pin(pumpPin), Device(manualTogglePin, statusLedPin) {}

void Pump::init() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  manualToggle.init();
  statusLed.init();
}

void Pump::on(EventInitiator initiator) {
  if (isActive) {
    COMM.send("Pump is already Off");
    return;
  }

  if(SYS.isDeviceLocked()) {
    COMM.send("Device is locked!");
    return;
  }

  digitalWrite(pin, HIGH);
  isActive = true;
  startTime = millis();
  statusLed.on();
  COMM.sendEvent(Event::PUMP_ON, initiator);
}

void Pump::off(EventInitiator initiator) {
  if (!isActive) {
    COMM.send("Pump is already Off");
    return;
  }

  if(SYS.isDeviceLocked()) {
    COMM.send("Device is locked!");
    return;
  }

  digitalWrite(pin, LOW);
  isActive = false;
  startTime = 0;
  statusLed.off();
  COMM.sendEvent(Event::PUMP_OFF, initiator);
}

void Pump::emergencyStop() {
  if (isActive) {
    digitalWrite(pin, LOW);
    isActive = false;
    startTime = 0;
    statusLed.off();
    COMM.sendEvent(Event::PUMP_SAFETY_STOP, EventInitiator::SAFETY);
    SYS.lockDevice(EventInitiator::SAFETY);
  }
}

void Pump::toggle(EventInitiator initiator) {
  if (isActive) {
    off(initiator);
  } else {
    on(initiator);
  }
}

JsonDocument Pump::getJsonData() const {
  JsonDocument doc;

  doc["type"] = "pump";
  doc["isActive"] = isActive;

  return doc;
};


void Pump::update() {
  manualToggle.update();

  if (manualToggle.wasPressed()) {
    toggle(EventInitiator::MANUAL);
  }

  if (isActive && isRunningTooLong()) {
    emergencyStop();
  }
}

bool Pump::isRunningTooLong() const {
  return isActive && (millis() - startTime >= MAX_PUMP_TIME);
}
