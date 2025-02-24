#include "../../../Inc/Sensor/PressureSensor/PressureSensor.h"

void PressureSensor_initDefault(PressureSensor* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

PressureSensorData PressureSensor_gatherDataDefault(PressureSensor* instance) {
  PressureSensorData defaultData = {0};
  instance->errorStatus.bits.defaultFunctionCalled = 1;
  return defaultData;
}