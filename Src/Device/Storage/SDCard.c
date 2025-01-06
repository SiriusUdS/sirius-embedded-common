#include "../../../Inc/Devices/Storage/SDCard.h"

void SDCard_init(Storage* instance) {
  instance->status.value = 0;
  instance->status.bits.initialized = 1;
}

void SDCard_storeAccelerometerData(Storage* instance, AccelerometerPacket data) {
  
}

void SDCard_storePressureSensorData(Storage* instance, PressureSensorPacket data) {
  
}