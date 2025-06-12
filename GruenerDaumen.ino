#include <Arduino.h>
#include "src/Sensor/MoistureSensor.h"
#include "src/Sensor/TemperatureSensor.h"
#include "src/Device/Pump.h"
#include "src/Config.h"
#include "src/Plant.h"
#include "src/Utils/Comm.h"
#include "src/Events.h"
#include "src/System.h"

const int MOISTURE_PIN = A0;
const int PUMP_PIN = 10;
const int TEMPARARUTE_PIN = 5;
const int BUTTON_PUMP_PIN = 2;
const int STATUS_PUMP_LED_PIN = 8;
const int BUTTON_4_NOT_USED = 7;

String commandBuffer;
boolean newCommand = false;

unsigned long lastCheck = 0;
const int PLANT_ARRAY_COUNTER = 1;
Plant plants[PLANT_ARRAY_COUNTER];

void setup() {
  COMM.init(9600);
  SYS.init();

  plants[0].addSensor(new MoistureSensor(MOISTURE_PIN));
  plants[0].addSensor(new TemperatureSensor(TEMPARARUTE_PIN));
  //plants[0].addSensor(new AirMoistureSensor());
  //plants[0].addSensor(new LightSensor());
  plants[0].addDevice(new Pump(PUMP_PIN, BUTTON_PUMP_PIN, STATUS_PUMP_LED_PIN));
  //plants[0].addDevice(new Lamp());
  //plants[0].addDevice(new Fan());

  for(Plant& plant : plants) {
    plant.init();
  }

  COMM.sendEvent(Event::SYSTEM_STARTED, EventInitiator::AUTO);
}

void loop() {
  handleCommands();
  handleUpdates();
  handleAutomation();
  handleCommunication();
}

void handleCommands() {
  static boolean recvInProgress = false;
  String readString;

  const size_t capacity = 512;
  StaticJsonDocument<capacity> doc;

  while (Serial.available() > 0 && newCommand == false) {
    readString = Serial.readStringUntil("\n");
    readString.trim();

    if (recvInProgress == true) {
      commandBuffer += readString;
    } else {
      recvInProgress = true;
      commandBuffer = readString;
    }

    DeserializationError error = deserializeJson(doc, commandBuffer);

    if(error) continue;

    recvInProgress = false;
    newCommand = true;
  }

  if(newCommand == false) return;

  newCommand = false;

  if(doc["type"] != "command") return;

  String target = doc["target"];
  if(target == "system"){
    // todo
  } else if (target == "plant") {
    int plantId = doc["plantId"];

    for(int i = 0; i < PLANT_ARRAY_COUNTER; i++) {
      if(plants[i].getId() != plantId) continue;
      
      plants[i].executeCommand(doc);
      return;
    }
  } else {
    COMM.send(String("Unknown target: " + target).c_str());
  }
}

void handleUpdates() {
  SYS.update();

  for(Plant& plant : plants) {
    plant.update();
  }
}

void handleAutomation() {}

void handleCommunication() {
  if((millis() - lastCheck) >= SEND_INTERVAL) {

    for(Plant& plant : plants) {
      JsonDocument doc;

      doc["timestamp"] = millis();
      doc["plant"] = doc;

      serializeJson(doc, Serial);
      Serial.println();
      // COMM.sendData(plant.getJsonData());
    }

    lastCheck = millis();
  }
}
