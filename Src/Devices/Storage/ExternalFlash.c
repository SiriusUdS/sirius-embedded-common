#include "../../../Inc/Devices/Storage/ExternalFlash.h"

void ExternalFlash_init(Storage* instance) {
  instance->status.value = 0;
  instance->status.bits.invalidFunctionPointer = 1;
}

void ExternalFlash_storeAccelerometerData(Storage* instance, AccelerometerPacket data) {
  instance->status.bits.invalidFunctionPointer = 1;
}

void ExternalFlash_storePressureSensorData(Storage* instance, PressureSensorPacket data) {
  instance->status.bits.invalidFunctionPointer = 1;
}