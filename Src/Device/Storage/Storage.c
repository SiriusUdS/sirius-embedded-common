#include "../../../Inc/Device/Storage/Storage.h"

void Storage_initDefault(Storage* instance) {
  instance->status.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Storage_storeAccelerometerDataDefault(Storage* instance, AccelerometerPacket data) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Storage_storePressureSensorDataDefault(Storage* instance, PressureSensorPacket data) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}