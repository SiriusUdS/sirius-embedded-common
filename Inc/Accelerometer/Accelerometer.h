#pragma once

struct Accelerometer;

typedef void (*Accelerometer_init)(struct Accelerometer* instance);

typedef void (*Accelerometer_gatherData)(struct Accelerometer* instance);

typedef struct {
  Accelerometer_init initFunction;
  Accelerometer_gatherData gatherDataFunction;
}
Accelerometer;

extern void Accelerometer_initDefault(Accelerometer* instance);

extern void Accelerometer_gatherDataDefault(Accelerometer* instance);