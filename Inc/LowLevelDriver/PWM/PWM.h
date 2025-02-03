#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/PWM/PWMErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/PWM/PWMStatus.h"

typedef void (*PWM_init)(struct PWM* instance);

typedef void (*PWM_setDutyCycle)(struct PWM* instance, uint8_t dutyCycle_pct);

typedef struct {
  PWM_init          init;
  PWM_setDutyCycle  setDutyCycle;

  uint8_t           minDutyCycle;
  uint8_t           maxDutyCycle;

  void*             externalInstance; // for now, used for HAL implementation

  uint8_t           timerId;
  uint8_t           channel;

  PWMErrorStatus    errorStatus;
  PWMStatus         status;
}
PWM;

extern void PWM_initDefault(PWM* instance);

extern void PWM_setDutyCycleDefault(PWM* instance, uint8_t dutyCycle_pct);