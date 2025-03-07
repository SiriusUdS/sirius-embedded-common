#include "../../../Inc/LowLevelDriver/GPIO/GPIO.h"

void GPIO_initDefault(GPIO* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

GPIOValue GPIO_readDefault(GPIO* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
  return 0;
}

void GPIO_writeDefault(GPIO* instance, GPIOValue value) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}