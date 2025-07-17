#pragma once

#include "../../../sirius-headers-common/Heater/HeaterErrorStatus.h"
#include "../../../sirius-headers-common/Heater/HeaterStatus.h"

#include "../../LowLevelDriver/GPIO/GPIO.h"

struct Heater;

typedef void (*Heater_init)(struct Heater* instance);

typedef void (*Heater_setDutyCycle)(struct Heater* instance, uint8_t dutyCycle_pct);

typedef void (*Heater_tick)(struct Heater* instance, uint32_t timestamp_ms);

typedef struct {
  Heater_init         init;
  Heater_setDutyCycle setDutyCycle_pct;
  Heater_tick         tick;

  GPIO* gpio;

  uint8_t currentDutyCycle_pct;
  uint8_t period_s;

  uint32_t lastSwitchTimestamp_ms;

  HeaterErrorStatus errorStatus;
  HeaterStatus      status;
}
Heater;

extern void Heater_initDefault(Heater* instance);

extern void Heater_setDutyCycleDefault(Heater* instance, uint8_t dutyCycle_pct);

extern void Heater_tickDefault(Heater* instance, uint32_t timestamp_ms);