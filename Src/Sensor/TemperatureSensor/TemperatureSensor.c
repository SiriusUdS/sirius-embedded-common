#include "../../../Inc/Sensor/TemperatureSensor/TemperatureSensor.h"

void TemperatureSensor_initDefault(TemperatureSensor* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

int16_t TemperatureSensor_readDataDefault(TemperatureSensor* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
  return 0;
}