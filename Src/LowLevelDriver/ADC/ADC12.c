#include "../../../Inc/LowLevelDriver/ADC/ADC12.h"

void ADC12_initDefault(ADC12* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

int16_t ADC12_getValueDefault(ADC12* instance) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
  return 0;
}