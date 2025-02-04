#include "PWM.h"

extern void PWMHAL_init(PWM* instance);

extern void PWMHAL_setDutyCycle(PWM* instance, uint16_t dutyCycle_CCR);