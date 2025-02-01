#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/PWM/PWMErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/PWM/PWMStatus.h"

typedef void (*PWM_init)(struct PWM* instance);

typedef void (*PWM_initStatic)();

typedef void (*PWM_setRatio)(struct PWM* instance);

typedef struct {
  PWM_init        init;
  PWM_initStatic  initStatic;
  void*           externalInstance; // for now, used for HAL implementation

  uint8_t         timerId;
  uint8_t         channel;

  PWMErrorStatus  errorStatus;
  PWMStatus       status;
}
PWM;

extern void PWM_initDefault(PWM* instance);

extern void PWM_setRatioDefault(PWM* instance);