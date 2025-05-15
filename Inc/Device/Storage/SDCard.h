#pragma once

#include <string.h>

#include "Storage.h"

typedef enum {
  SD_CARD_STATUS_FILE,
  SD_CARD_STATE_FILE,
  SD_CARD_ADC_FILE,
  SD_CARD_ADC_TIMESTAMP_FILE
}
SDCardFileIndex;

#define SD_CARD_BASE_DIRECTORY_PATH "000/"

#define SD_CARD_LOAD_PATH          "LOAD.hex"
#define SD_CARD_STATE_PATH         "STATES.hex"
#define SD_CARD_ADC_PATH           "ADC.hex"
#define SD_CARD_ADC_TIMESTAMP_PATH "ADCT.hex"

void SDCard_init(Storage* instance);

void SDCard_store(Storage* instance, SDCardFileIndex destination, uint8_t* data, uint16_t size);

void SDCard_fetch(Storage* instance, SDCardFileIndex destination, uint8_t* data, uint16_t size);