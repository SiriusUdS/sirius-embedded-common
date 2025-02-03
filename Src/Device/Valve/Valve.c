#include "../../../Inc/Device/Valve/Valve.h"

void Valve_initDefault(Valve* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;

  instance->gatherData = Valve_gatherDataDefault;
  instance->setDutyCycle = Valve_setDutyCycleDefault;
}

void Valve_gatherDataDefault(Valve* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Valve_setDutyCycleDefault(Valve* instance, uint8_t ratio_pct) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}