#include "../../../Inc/LowLevelDriver/PWM/PWMHAL.h"

static uint8_t initHandle(PWM* instance);

void PWMHAL_init(PWM* instance) {
  initHandle(instance);
}
