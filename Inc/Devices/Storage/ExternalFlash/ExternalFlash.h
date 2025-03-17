#pragma once
// DATASHEET : https://ww1.microchip.com/downloads/en/DeviceDoc/20005045C.pdf
#include "stm32f4xx_hal.h"
#include "stm32f411xe.h"
#include <stdint.h>

// TABLE 4-4 
#define CHIP_ERASE 0x60
#define RD 0x03
#define AAI 0xAD
#define RDSR 0x05
#define WRSR 0x01
#define ERASE 0x20
#define WREN 0x06
#define WRDI 0x04
#define EWSR 0x50

#define PCKG_SIZE_BYTE 2

#define T_SE_MS 25
#define T_SCE_MS 50
#define T_BP_US 1


typedef struct {
    uint8_t busy : 1;
    uint8_t wel : 1;
    uint8_t BP0 : 1;
    uint8_t BP1 : 1;
    uint8_t BP2 : 1;
    uint8_t BP3 : 1;
    uint8_t aai : 1;
    uint8_t bpl : 1;
}StatusRegister;


enum FlashStatus{
    WRITE,
    READ,
    RESET_FLASH
};

enum FlashFeedBack {
    SUCCESS_FLASH,
    FAILED
};

typedef struct {
    SPI_HandleTypeDef *hspi;
    StatusRegister actualRegister;
    int fixTime;
}ExternalFlash;

void FLASH_init(SPI_HandleTypeDef *hspi, int fixTime);

int FLASH_write(uint8_t* addr, uint8_t* din, size_t size);
int FLASH_read(uint8_t* addr, uint8_t* dout, size_t size);

int FLASH_ERASE(uint8_t* addr);

void FLASH_readStatusRegister(StatusRegister* reg);


/*

WREN
while{
    AAI
    Wait RDSR busy bit = 0
}
WRDI
RDSR

*/