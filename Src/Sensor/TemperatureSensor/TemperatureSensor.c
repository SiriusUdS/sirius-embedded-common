#include "../../../Inc/Sensor/TemperatureSensor/TemperatureSensor.h"

TemperatureSensorData defaultData = {0};
void TemperatureSensor_initDefault(TemperatureSensor* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

TemperatureSensorData TemperatureSensor_readDataDefault(TemperatureSensor* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
  
  return defaultData;
}