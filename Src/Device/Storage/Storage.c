#include "../../../Inc/Device/Storage/Storage.h"

void Storage_initDefault(Storage* instance) {
  instance->status.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Storage_storeDefault(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Storage_fetchDefault(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void Storage_tickDefault(Storage* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}