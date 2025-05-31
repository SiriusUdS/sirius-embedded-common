#pragma once

#include "../../../sirius-headers-common/Igniter/IgniterErrorStatus.h"
#include "../../../sirius-headers-common/Igniter/IgniterStatus.h"

#include "../../LowLevelDriver/GPIO/GPIO.h"

typedef void (*Igniter_init)(struct Igniter* instance);

typedef void (*Igniter_ignite)(struct Igniter* instance, uint32_t timestamp_ms);

typedef void (*Igniter_tick)(struct Igniter* instance, uint32_t timestamp_ms);

typedef struct {
  Igniter_init   init;
  Igniter_ignite ignite;
  Igniter_tick   tick;

  GPIO* gpio;

  uint32_t igniteTimestamp_ms;
  uint32_t igniteDuration_ms;

  IgniterErrorStatus errorStatus;
  IgniterStatus      status;
}
Igniter;

extern void Igniter_initDefault(Igniter* instance);

extern void Igniter_igniteDefault(Igniter* instance, uint32_t timestamp_ms);

extern void Igniter_tickDefault(Igniter* instance, uint32_t timestamp_ms);