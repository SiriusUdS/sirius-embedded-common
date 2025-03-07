#include "../../../Inc/Sensor/TemperatureSensor/TemperatureSensor.h"

void TemperatureSensor_initDefault(TemperatureSensor* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void TemperatureSensor_tickDefault(TemperatureSensor* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}