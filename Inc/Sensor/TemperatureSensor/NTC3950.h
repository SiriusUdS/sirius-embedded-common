#pragma once

#include "TemperatureSensor.h"

extern void NTC3950_init(TemperatureSensor* instance);

extern TemperatureSensorData NTC3950_readData(TemperatureSensor* instance);