#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>
#include <cstring>

enum class EventInitiator {
    MANUAL,
    AUTO,
    SAFETY,
    REMOTE
};

enum class Event {
    SYSTEM_STARTED,
    PUMP_ON,
    PUMP_OFF,
    PUMP_SAFETY_STOP,
    SYSTEM_LOCK,
    SYSTEM_UNLOCK,
    MODE_AUTO,
    MODE_MANUAL
};

inline const char* toString(EventInitiator initiator) {
    switch (initiator) {
        case EventInitiator::MANUAL: return "manual";
        case EventInitiator::AUTO:   return "auto";
        case EventInitiator::SAFETY: return "safety";
        case EventInitiator::REMOTE: return "remote";
    }
    return "unknown";
}

inline const char* toString(Event event) {
    switch (event) {
        case Event::SYSTEM_STARTED:   return "system_started";
        case Event::PUMP_ON:          return "pump_on";
        case Event::PUMP_OFF:         return "pump_off";
        case Event::PUMP_SAFETY_STOP: return "pump_safety_stop";
        case Event::SYSTEM_LOCK:      return "system_lock";
        case Event::SYSTEM_UNLOCK:    return "system_unlock";
        case Event::MODE_AUTO:        return "mode_auto";
        case Event::MODE_MANUAL:      return "mode_manual";
    }
    return "unknown";
}

inline const char* getMessage(Event event) {
    switch (event) {
        case Event::SYSTEM_STARTED:   return "System has started.";
        case Event::PUMP_ON:          return "Pump was turned on.";
        case Event::PUMP_OFF:         return "Pump was turned off.";
        case Event::PUMP_SAFETY_STOP: return "Pump stopped for safety reasons.";
        case Event::SYSTEM_LOCK:      return "System is now Locked.";
        case Event::SYSTEM_UNLOCK:    return "System is now Unlocked.";
        case Event::MODE_AUTO:        return "Switching to Auto Mode.";
        case Event::MODE_MANUAL:      return "Switching to Manual Mode.";
    }
    return "Unknown event.";
}

inline Event eventFromString(const char* id) {
    if (strcmp(id, "system_started") == 0) return Event::SYSTEM_STARTED;
    if (strcmp(id, "pump_on") == 0) return Event::PUMP_ON;
    if (strcmp(id, "pump_off") == 0) return Event::PUMP_OFF;
    if (strcmp(id, "pump_safety_stop") == 0) return Event::PUMP_SAFETY_STOP;
    if (strcmp(id, "system_lock") == 0) return Event::SYSTEM_LOCK;
    if (strcmp(id, "system_unlock") == 0) return Event::SYSTEM_UNLOCK;
    if (strcmp(id, "mode_auto") == 0) return Event::MODE_AUTO;
    if (strcmp(id, "mode_manual") == 0) return Event::MODE_MANUAL;
    return Event::SYSTEM_STARTED;
}

#endif
