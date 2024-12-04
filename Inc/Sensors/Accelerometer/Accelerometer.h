#pragma once

#include "../../sirius-headers-common/Accelerometer/AccelerometerData.h"

struct Accelerometer;

typedef void (*Accelerometer_init)(struct Accelerometer* instance);

typedef void (*Accelerometer_gatherData)(struct Accelerometer* instance, AccelerometerData* rawData);

typedef struct {
  Accelerometer_init initFunction;
  Accelerometer_gatherData gatherDataFunction;

  AccelerometerStatus status;
}
Accelerometer;

extern void Accelerometer_initDefault(Accelerometer* instance);

extern void Accelerometer_gatherDataDefault(Accelerometer* instance, AccelerometerData* rawData);