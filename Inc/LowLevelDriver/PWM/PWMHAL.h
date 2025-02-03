#include "PWM.h"

extern void PWMHAL_init(PWM* instance);

extern void PWMHAL_setDutyCycle(PWM* instance, uint8_t dutyCycle_pct);