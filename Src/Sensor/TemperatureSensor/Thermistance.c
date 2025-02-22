#include "../../../Inc/Sensor/TemperatureSensor/Thermistance.h"

TemperatureSensorData currentData = 0;

void Thermistance_init(TemperatureSensor* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

TemperatureSensorData Thermistance_readData(TemperatureSensor* instance) {
  currentData.rawTemperature = instance->adc->getValue(instance->adc);
  return currentData;
}