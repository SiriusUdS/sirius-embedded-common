#include "../../../Inc/Sensor/PressureSensor/PressureSensor.h"

void PressureSensor_initDefault(PressureSensor* instance) {
  instance->status.value = 0;
  instance->status.bits.invalidFunctionPointer = 1;

  instance->gatherData = PressureSensor_gatherDataDefault;
}

void PressureSensor_gatherDataDefault(PressureSensor* instance) {
  instance->status.bits.invalidFunctionPointer = 1;

  
}