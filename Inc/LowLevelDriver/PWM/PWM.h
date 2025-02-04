#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/PWM/PWMErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/PWM/PWMStatus.h"

typedef void (*PWM_init)(struct PWM* instance);

typedef void (*PWM_setDutyCycle)(struct PWM* instance, uint8_t dutyCycle_pct);

typedef struct {
  PWM_init         init;
  PWM_setDutyCycle setDutyCycle;

  uint8_t minDutyCycle_CCR;
  uint8_t maxDutyCycle_CCR;

  // for now, used for HAL comptatibility
  void* externalHandle; 
  void* timer;

  // When used with HAL, both = 0
  uint8_t timerId;
  uint8_t channel;

  uint16_t prescaler;
  uint16_t autoReload;
  uint16_t comparator;

  int16_t       currentDutyCycle_CCR;
  unsigned long lastDutyCycleChangeTime_ms;

  PWMErrorStatus errorStatus;
  PWMStatus      status;
}
PWM;

extern void PWM_initDefault(PWM* instance);

extern void PWM_setDutyCycleDefault(PWM* instance, uint8_t dutyCycle_pct);