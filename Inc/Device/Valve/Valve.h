#pragma once

#include "../../../sirius-headers-common/Valve/ValveErrorStatus.h"
#include "../../../sirius-headers-common/Valve/ValveStatus.h"

#include "../../LowLevelDriver/PWM/PWM.h"

struct Valve;

typedef void (*Valve_init)(struct Valve* instance);

typedef void (*Valve_gatherData)(struct Valve* instance);

typedef void (*Valve_setDutyCycle)(struct Valve* instance, uint32_t ratio_pct);

typedef void (*Valve_close)(struct Valve* instance);

typedef void (*Valve_open)(struct Valve* instance);

typedef void (*Valve_tick)(struct Valve* instance);

typedef struct {
  Valve_init         init;
  Valve_gatherData   gatherData;
  Valve_setDutyCycle setDutyCycle;
  Valve_close        close;
  Valve_open         open;
  Valve_tick         tick;

  PWM*                pwm;

  int16_t             targetDutyCycle_CCR;

  ValveErrorStatus    errorStatus;
  ValveStatus         status;
}
Valve;

extern void Valve_initDefault(Valve* instance);

extern void Valve_gatherDataDefault(Valve* instance);

extern void Valve_setDutyCycleDefault(Valve* instance, uint32_t ratio_pct);

extern void Valve_closeDefault(Valve* instance);

extern void Valve_openDefault(Valve* instance);

extern void Valve_tickDefault(Valve* instance);