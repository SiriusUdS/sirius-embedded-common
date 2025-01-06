#include "../../../Inc/Devices/Storage/ExternalFlash.h"

void ExternalFlash_init(Storage* instance) {
  instance->status.value = 0;
  instance->status.bits.initialized = 1;
}

void ExternalFlash_storeAccelerometerData(Storage* instance, AccelerometerPacket data) {
  
}

void ExternalFlash_storePressureSensorData(Storage* instance, PressureSensorPacket data) {
  
}