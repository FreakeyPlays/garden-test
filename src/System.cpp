#include "System.h"
#include "Utils/Comm.h"
#include "Events.h"

System& System::getInstance() {
    static System instance;
    return instance;
}

void System::init() {
    systemUnlockButton.init();
    modeToggle.init();
    systemLockedLed.init();
    modeLed.init();
}

void System::update() {
    systemUnlockButton.update();
    modeToggle.update();

    if (systemUnlockButton.wasPressed()) {
        unlockDevice();
    }

    if (modeToggle.wasPressed()) {
        toggleMode(EventInitiator::MANUAL);
    }
}

void System::lockDevice(EventInitiator initiator) {
    if (!locked) {
        locked = true;
        systemLockedLed.on();
        COMM.sendEvent(Event::SYSTEM_LOCK, initiator);
        return;
    }

    COMM.send("Device is Already locked.");
}

void System::unlockDevice() {
    if (locked) {
        locked = false;
        systemLockedLed.off();
        COMM.sendEvent(Event::SYSTEM_UNLOCK, EventInitiator::MANUAL);
        return;
    }

    COMM.send("Device is Already unlocked.");
}

void System::setAutoMode(EventInitiator initiator) {
    if (manualMode) {
        manualMode = false;
        modeLed.off();
        COMM.sendEvent(Event::MODE_AUTO, initiator);
        return;
    }

    COMM.send("Auto mode is already active.");
}

void System::setManualMode(EventInitiator initiator) {
    if (!manualMode) {
        manualMode = true;
        modeLed.on();
        COMM.sendEvent(Event::MODE_MANUAL, initiator);
        return;
    }

    COMM.send("Manual mode is already active.");
}

void System::toggleMode(EventInitiator initiator) {
    if(manualMode) {
        setAutoMode(initiator);
    } else {
        setManualMode(initiator);
    }
}

void System::executeCommand(const JsonDocument& doc) {
}

JsonDocument System::getJsonData() const {
    JsonDocument doc;

    doc["manualMode"] = manualMode;
    doc["locked"] = locked;

    return doc;
}

bool System::addPlant(const Plant& plant) {
    if (plantCount >= MAX_PLANTS) {
        COMM.send("Max. Plant Count reached!");
        return false;
    }

    plants[plantCount++] = plant;
    return true;
}

int System::getPlantCount() const {
    return plantCount;
}

const Plant* System::getPlant(int id) const {
    for(int i = 0; i < plantCount; i++) {
        if(plants[i].getId() != id) continue;
        
        return &plants[i];
    }

    COMM.send("Plant was not found");
    return nullptr;
}