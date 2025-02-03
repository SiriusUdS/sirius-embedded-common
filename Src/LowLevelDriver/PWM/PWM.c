#include "../../../Inc/LowLevelDriver/PWM/PWM.h"

void PWM_initDefault(PWM* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void PWM_setDutyCycleDefault(PWM* instance, uint8_t dutyCycle_pct) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}