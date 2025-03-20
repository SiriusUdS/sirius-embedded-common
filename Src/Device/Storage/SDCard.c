#include "../../../Inc/Device/Storage/SDCard.h"

void SDCard_init(Storage* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

void SDCard_store4kbData(Storage* instance, uint8_t* data) {
  
}

void SDCard_fetch4kbData(Storage* instance, uint8_t* data) {
  
}