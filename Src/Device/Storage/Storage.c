#include "../../../Inc/Device/Storage/Storage.h"

void Storage_initDefault(Storage* instance) {
  instance->status.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;

  instance->store = (Storage_store)Storage_storeDefault;
  instance->fetch = (Storage_fetch)Storage_fetchDefault;
  instance->tick  = (Storage_tick)Storage_tickDefault;
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