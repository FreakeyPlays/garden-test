#ifndef EVENTS_H
#define EVENTS_H

namespace EventInitiator {
    constexpr const char* MANUAL   = "manual";
    constexpr const char* AUTO     = "auto";
    constexpr const char* SAFETY   = "safety";
    constexpr const char* REMOTE   = "remote";
  }

namespace Event {
  constexpr const char* SYSTEM_STARTED  = "system_started";
  constexpr const char* PUMP_ON    = "pump_on";
  constexpr const char* PUMP_OFF    = "pump_off";
  constexpr const char* PUMP_SAFETY_STOP= "pump_safety_stop";
  constexpr const char* SYSTEM_LOCK= "system_lock";
  constexpr const char* SYSTEM_UNLOCK= "system_unlock";
  constexpr const char* MODE_AUTO= "mode_auto";
  constexpr const char* MODE_MANUAL= "mode_manual";

  inline const char* getMessage(const char* event) {
    if (event == SYSTEM_STARTED) return "System has started.";
    if (event == PUMP_ON) return "Pump was turned on.";
    if (event == PUMP_OFF) return "Pump was turned off.";
    if (event == PUMP_SAFETY_STOP) return "Pump stopped for safety reasons.";
    if (event == SYSTEM_LOCK) return "System is now Locked.";
    if (event == SYSTEM_UNLOCK) return "System is now Unlocked.";
    if (event == MODE_AUTO) return "Switching to Auto Mode.";
    if (event == MODE_MANUAL) return "Switching to Manual Mode.";
    return "Unknown event.";
  }
}

#endif
