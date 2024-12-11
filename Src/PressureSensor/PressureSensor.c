#include "../../Inc/Sensors/PressureSensor/PressureSensor.h"

void PressureSensor_initDefault(PressureSensor* instance) {
  instance->status.value = 0;
  instance->status.bits.invalidFunctionPointer = 1;
}

void PressureSensor_gatherDataDefault(PressureSensor* instance) {
  instance->status.bits.invalidFunctionPointer = 1;
}