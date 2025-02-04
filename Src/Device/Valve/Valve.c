#include "../../../Inc/Device/Valve/Valve.h"

void Valve_initDefault(Valve* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;

  instance->gatherData = (Valve_gatherData)Valve_gatherDataDefault;
  instance->setDutyCycle = (Valve_setDutyCycle)Valve_setDutyCycleDefault;
  instance->tick = (Valve_tick)Valve_tickDefault;
}

void Valve_gatherDataDefault(Valve* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Valve_setDutyCycleDefault(Valve* instance, uint32_t dutyCycle_pct) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Valve_tickDefault(Valve* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}