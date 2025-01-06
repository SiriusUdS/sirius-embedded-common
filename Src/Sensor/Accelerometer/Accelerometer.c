#include "../../../Inc/Sensor/Accelerometer/Accelerometer.h"

void Accelerometer_initDefault(Accelerometer* instance) {
  instance->status.value = 0;
  instance->status.bits.invalidFunctionPointer = 1;

  instance->gatherData = Accelerometer_gatherDataDefault;
}

void Accelerometer_gatherDataDefault(Accelerometer* instance, AccelerometerAxis* rawData) {
  instance->status.value = 0;
  instance->status.bits.invalidFunctionPointer = 1;

  rawData->x = 0;
  rawData->y = 0;
  rawData->z = 0;
}