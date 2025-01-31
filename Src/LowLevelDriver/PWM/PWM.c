#include "../../../Inc/LowLevelDriver/PWM/PWM.h"

void PWM_initDefault(PWM* instance) {
  instance->status.bits.invalidFunctionPointer = 1;
}