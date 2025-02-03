#pragma once

#include "Valve.h"

/*
FREQ = CLOCKFREQ/(PSC+1)*(ARR+1)

PSC = CLOCKFREQ/FREQ(ARR+1)-1
*/

#define SG90_OPERATING_FREQUENCY_HZ 50
#define SG90_PSC 59
#define SG90_ARR 32031
#define CLOCK_FREQUENCY_HZ 96000000

extern void SG90_init(Valve* instance);

extern void SG90_gatherData(Valve* instance);

extern void SG90_setDutyCycle(Valve* instance, uint8_t dutyCycle_pct);