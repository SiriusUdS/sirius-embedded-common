#pragma once

#include <string.h>

#include "Storage.h"

#define SD_CARD_LOAD_PATH          "LOAD.hex"
#define SD_CARD_STATE_PATH         "STATES.hex"
#define SD_CARD_ADC_PATH           "ADC.hex"
#define SD_CARD_ADC_TIMESTAMP_PATH "ADCT.hex"

#define SD_CARD_STORES_BETWEEN_SYNC (uint8_t)0x10

void SDCard_init(Storage* instance);

void SDCard_store(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

void SDCard_fetch(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

void SDCard_tick(Storage* instance, uint32_t timestamp_ms);