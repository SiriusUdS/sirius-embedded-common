#include "../../../Inc/Device/Button/Button.h"

void Button_initDefault(Button* instance) {
  instance->tick = (Button_tick)Button_tickDefault;
  instance->errorStatus.value = 0;
  instance->status.value = 0;

  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Button_tickDefault(Button* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}