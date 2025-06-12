#ifndef SYSTEM_H
#define SYSTEM_H

#define SYS System::getInstance()

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Utils/Button.h"
#include "Utils/Led.h"
#include "Plant.h"
#include "Events.h"

const int MODE_TOGGLE_PIN = 3;
const int UNLOCK_BUTTON_PIN = 6;
const int DEVICE_LOCKED_LED = 9;
const int MODE_LED = 10;

class System {
public:
    static System& getInstance();

    void init();
    void update();

    void lockDevice(EventInitiator initiator = EventInitiator::AUTO);
    void unlockDevice();

    void setAutoMode(EventInitiator initiator = EventInitiator::AUTO);
    void setManualMode(EventInitiator initiator = EventInitiator::AUTO);
    void toggleMode(EventInitiator initiator = EventInitiator::AUTO);

    void executeCommand(const JsonDocument& doc);

    bool isDeviceLocked() const { return locked; }

    JsonDocument getJsonData() const;

    bool addPlant(const Plant& plant);
    int getPlantCount() const;
    const Plant* getPlant(int id) const;

private:
    System(): systemLockedLed(DEVICE_LOCKED_LED), modeLed(MODE_LED), systemUnlockButton(UNLOCK_BUTTON_PIN), modeToggle(MODE_TOGGLE_PIN) {}
    System(const System&) = delete;
    System& operator=(const System&) = delete;

    static const int MAX_PLANTS = 3;
    Plant plants[MAX_PLANTS];
    int plantCount;


    bool locked = false;
    Button systemUnlockButton;
    Led systemLockedLed;
    bool manualMode = false;
    Button modeToggle;
    Led modeLed;
};

#endif
