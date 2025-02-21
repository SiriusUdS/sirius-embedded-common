#include "../../../Inc/Sensor/PressureSensor/PressureSensor.h"

void PressureSensor_initDefault(PressureSensor* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void PressureSensor_gatherDataDefault(PressureSensor* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}