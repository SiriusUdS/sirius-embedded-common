#include "../../../Inc/Device/Igniter/Igniter.h"

void Igniter_initDefault(Igniter* instance) {
  instance->ignite = (Igniter_ignite)Igniter_igniteDefault;
  instance->tick = (Igniter_tick)Igniter_tickDefault;
  instance->errorStatus.value = 0;
  instance->status.value = 0;

  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Igniter_igniteDefault(Igniter* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Igniter_tickDefault(Igniter* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}