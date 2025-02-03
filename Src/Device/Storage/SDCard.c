#include "../../../Inc/Device/Storage/SDCard.h"

void SDCard_init(Storage* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

void SDCard_storeAccelerometerData(Storage* instance, AccelerometerPacket data) {
  
}

void SDCard_storePressureSensorData(Storage* instance, PressureSensorPacket data) {
  
}