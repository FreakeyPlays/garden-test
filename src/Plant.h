#ifndef PLANT_H
#define PLANT_H

#include <ArduinoJson.h>
#include "Sensor/Sensor.h"
#include "Device/Device.h"

class Plant {
    private:
        static int nextId;
        int id;

        Sensor* sensors[2];
        int sensorCount = 0;
        Device* devices[1];
        int deviceCount = 0;

        unsigned long lastChecked = 0;

        int targetMoisture = 80;
        int targetTemp = 24;

    public:
        Plant();

        void init();
        void update();
        JsonDocument getJsonData() const;

        void addSensor(Sensor* sensor);
        void addDevice(Device* device);

        void setTargetMoisture(int target) { targetMoisture = target; }
        void setTargetTemp(int target) { targetTemp = target; }

        int getId() { return id; }

        void executeCommand(const JsonDocument& doc);
};

#endif