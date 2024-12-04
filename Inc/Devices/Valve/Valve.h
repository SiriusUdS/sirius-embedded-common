#pragma once

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
}
Valve;

extern void Valve_initDefault(Valve* instance);