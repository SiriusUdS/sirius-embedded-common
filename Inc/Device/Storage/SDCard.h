#pragma once

#include <string.h>

#include "Storage.h"

#define SD_CARD_LOAD_PATH          "LOAD.hex"
#define SD_CARD_STATE_PATH         "STATES.hex"
#define SD_CARD_ADC_PATH           "ADC.hex"
#define SD_CARD_ADC_TIMESTAMP_PATH "ADCT.hex"

#define SD_CARD_STORES_BETWEEN_SYNC (uint8_t)0x10

#define SD_CARD_BUFFER_SIZE_BYTES 0x10000
#define SD_CARD_FOOTER_SIZE_BYTES 0x80
#define SD_CARD_FOOTER_SIGNATURE_SIZE_BYTES 0x40

typedef struct {
  uint32_t timestamp_ms;
  uint16_t status;
  uint16_t errorStatus;
  uint16_t valveStatus[2];
  uint16_t valveErrorStatus[2];
  uint8_t padding[44];
  uint32_t signature[SD_CARD_FOOTER_SIGNATURE_SIZE_BYTES / (sizeof(uint32_t))];
  uint32_t crc;
}
SDBufferFooter;

typedef struct {
  uint8_t data[SD_CARD_BUFFER_SIZE_BYTES - sizeof(SDBufferFooter)];
  SDBufferFooter footer;
}
SDFormattedData;

typedef union {
  uint16_t values[SD_CARD_BUFFER_SIZE_BYTES / sizeof(uint16_t)];

  SDFormattedData sdData;

  uint8_t hex[SD_CARD_BUFFER_SIZE_BYTES];
}
SDCardBuffer;

void SDCard_init(Storage* instance);

void SDCard_store(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

void SDCard_fetch(Storage* instance, StorageDestination destination, uint8_t* data, uint16_t size);

void SDCard_tick(Storage* instance, uint32_t timestamp_ms);