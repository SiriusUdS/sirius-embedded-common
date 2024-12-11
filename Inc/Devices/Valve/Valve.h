#pragma once

#include "../../../sirius-headers-common/Valve/ValveStatus.h"

struct Valve;

typedef enum {
  VALVE_CLOSED,
  VALVE_OPENED
}
ValveState;

typedef void (*Valve_init)(struct Valve* instance);

typedef void (*Valve_gatherData)(struct Valve* instance);

typedef void (*Valve_setState)(struct Valve* instance, ValveState state);

typedef struct {
  Valve_init initFunction;
  Valve_gatherData gatherDataFunction;
  Valve_setState setStateFunction;

  ValveStatus status;
}
Valve;

extern void Valve_initDefault(Valve* instance);

extern void Valve_gatherDataDefault(Valve* instance);

extern void Valve_setStateDefault(Valve* instance, ValveState state);