#pragma once

#include "Storage.h"
#include "../../LowLevelDriver/GPIO/GPIO.h"

typedef struct SD_CARD 
{
    Storage * storage; // Inherit from Storage structure
    SPI_HandleTypeDef * spiHandle; // Pointer to SPI handle
    GPIO * ce; // Chip Enable pin
}sd_card_t;


void SDCard_spi_init(Storage* instance);
void SDCard_spi_store4kbDataDefault(Storage* instance, uint8_t* data);
void SDCard_spi_fetch4kbDataDefault(Storage* instance, uint8_t* data);