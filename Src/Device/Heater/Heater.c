#include "../../../Inc/Device/Heater/Heater.h"

void Heater_initDefault(Heater* instance) {
  instance->setDutyCycle_pct = (Heater_setDutyCycle)Heater_setDutyCycleDefault;
  instance->tick = (Heater_tick)Heater_tickDefault;
  instance->errorStatus.value = 0;
  instance->status.value = 0;

  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Heater_setDutyCycleDefault(Heater* instance, uint8_t dutyCycle_pct) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Heater_tickDefault(Heater* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}