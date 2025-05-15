#include "../../../Inc/Device/Storage/ExternalFlash.h"

void ExternalFlash_init(Storage* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

void ExternalFlash_store(Storage* instance, uint8_t* data, uint16_t size) {
  
}

void ExternalFlash_fetch(Storage* instance, uint8_t* data, uint16_t size) {
  
}