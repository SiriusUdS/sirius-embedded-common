#pragma once

#include "TemperatureSensor.h"

extern void Thermistance_init(TemperatureSensor* instance);

extern int16_t Thermistance_readData(TemperatureSensor* instance);