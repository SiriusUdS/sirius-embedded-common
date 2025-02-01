#pragma once

#include "../../../sirius-headers-common/PressureSensor/PressureSensorData.h"

struct PressureSensor;

typedef void (*PressureSensor_init)(struct PressureSensor* instance);

typedef void (*PressureSensor_gatherData)(struct PressureSensor* instance);

typedef struct {
  PressureSensor_init       init;
  PressureSensor_gatherData gatherData;

  PressureSensorValue       data;
  PressureSensorStatus      status;
}
PressureSensor;

extern void PressureSensor_initDefault(PressureSensor* instance);

extern void PressureSensor_gatherDataDefault(PressureSensor* instance);