#ifndef COMM_H
#define COMM_H

#define COMM Comm::getInstance()

#include <Arduino.h>
#include <ArduinoJson.h>
#include "../Events.h"

class Comm {
  public:
    static Comm& getInstance();

    void init(unsigned long baudRate = 9600);

    void send(const char* msg);
    void sendEvent(Event event, EventInitiator initiator);
    void sendData(JsonDocument doc);

  private:
    Comm() {}
    Comm(const Comm&) = delete;
    Comm& operator=(const Comm&) = delete;
};

#endif
