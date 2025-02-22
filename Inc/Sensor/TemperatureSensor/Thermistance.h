#pragma once

#include "TemperatureSensor.h"

extern void Thermistance_init(TemperatureSensor* instance);

extern TemperatureSensorData Thermistance_readData(TemperatureSensor* instance);