#pragma once

#include "../../../sirius-headers-common/Valve/ValveErrorStatus.h"
#include "../../../sirius-headers-common/Valve/ValveStatus.h"

#include "../../LowLevelDriver/PWM/PWM.h"

struct Valve;

typedef void (*Valve_init)(struct Valve* instance);

typedef void (*Valve_gatherData)(struct Valve* instance);

typedef void (*Valve_setDutyCycle)(struct Valve* instance, uint8_t ratio_pct);

typedef struct {
  Valve_init          init;
  Valve_gatherData    gatherData;
  Valve_setDutyCycle  setRatio;

  PWM                 pwmDriver;

  ValveErrorStatus    errorStatus;
  ValveStatus         status;
}
Valve;

extern void Valve_initDefault(Valve* instance);

extern void Valve_gatherDataDefault(Valve* instance);

extern void Valve_setDutyCycleDefault(Valve* instance, uint8_t ratio_pct);