#include "../../../Inc/Sensor/TemperatureSensor/NTC3950.h"

void NTC3950_init(TemperatureSensor* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

TemperatureSensorData NTC3950_readData(TemperatureSensor* instance) {
  TemperatureSensorData currentData = {0};
  
  currentData.rawTemperature = instance->adc->getValue(instance->adc);
  return currentData;
}