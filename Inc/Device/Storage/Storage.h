#pragma once

#include <stdint.h>

#include "../../../sirius-headers-common/Storage/StorageStatus.h"
#include "../../../sirius-headers-common/Storage/StorageErrorStatus.h"
#include "../../../sirius-headers-common/Storage/StorageState.h"

struct Storage;

typedef enum {
  STORAGE_LOAD_DESTINATION,
  STORAGE_STATE_DESTINATION,
  STORAGE_ADC_DESTINATION,
  STORAGE_ADC_TIMESTAMP_DESTINATION
}
StorageDestination;

typedef void (*Storage_init)(struct Storage* instance);

typedef void (*Storage_store)(struct Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

typedef void (*Storage_fetch)(struct Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

typedef void (*Storage_tick)(struct Storage* instance, uint32_t timestamp_ms);

typedef struct {
  Storage_init  init;
  Storage_store store;
  Storage_fetch fetch;
  Storage_tick  tick;

  void* externalInstance;
  void* fs;
  char* volumePath;

  uint8_t state;

  StorageErrorStatus errorStatus;
  StorageStatus      status;
}
Storage;

void Storage_initDefault(Storage* instance);

void Storage_storeDefault(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

void Storage_fetchDefault(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

void Storage_tickDefault(Storage* instance, uint32_t timestamp_ms);