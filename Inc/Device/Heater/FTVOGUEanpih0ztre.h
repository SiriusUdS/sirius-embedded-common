#pragma once

#include "Heater.h"

extern void FTVOGUEanpih0ztre_init(Heater* instance);

extern void FTVOGUEanpih0ztre_setDutyCycle(Heater* instance, uint8_t dutyCycle_pct);

extern void FTVOGUEanpih0ztre_tick(Heater* instance, uint32_t timestamp_ms);