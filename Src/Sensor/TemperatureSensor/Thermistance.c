#include "../../../Inc/Sensor/TemperatureSensor/Thermistance.h"

void Thermistance_init(TemperatureSensor* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

int16_t Thermistance_readData(TemperatureSensor* instance) {
  return instance->adc->getValue(instance->adc);
}