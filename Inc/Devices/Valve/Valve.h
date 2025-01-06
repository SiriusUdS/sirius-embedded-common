#pragma once

// VERIFY THIS SECTION
#include "stm32f4xx_hal.h"
#include "stm32f411xe.h"
#include <stdint.h>

#define PWM_DUTY_CYCLE_MIN 0
#define PWM_DUTY_CYCLE_MAX 100 // FOR ARR OF 100
//SET THE PWM CONTROLLER TO CHANNEL 1 AND THE ARR FOR THE DESIRE FREQ
//SOURCE : https://controllerstech.com/pwm-in-stm32/

#define ELAPSED_DELAY_MS 50
#define ELAPSED_STEP 1

struct Valve;

typedef enum {
  VALVE_CLOSED,
  VALVE_OPENED,
  VALVE_PENDING
}
ValveState;

typedef void (*Valve_init)(struct Valve* instance);

typedef void (*Valve_gatherData)(struct Valve* instance);

typedef void (*Valve_setState)(struct Valve* instance, ValveState state);

typedef struct {
  Valve_init initFunction;
  ValveState state;
  uint16_t actualCycle;
  unsigned long CycleLastTime;
}
Valve;


void VALVE_init();
void VALVE_SetState(ValveState _state);
uint16_t VALVE_GetActualCycle();
ValveState VALVE_GetState();

extern void Valve_initDefault(Valve* instance);