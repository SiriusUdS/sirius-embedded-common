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
#define ERASE 0x20
#define WREN 0x06
#define WRDI 0x04

#define PCKG_SIZE_BYTE 2

#define T_SE_MS 25
#define T_SCE_MS 50
#define T_BP_US 10


typedef struct {
    int busy : 1;
    int wel : 1;
    int BP0 : 1;
    int BP1 : 1;
    int BP2 : 1;
    int BP3 : 1;
    int aai : 1;
    int bpl : 1;
}StatusRegister;


enum FlashStatus{
    WRITE,
    READ,
    RESET
};

enum FlashFeedBack {
    SUCCESS,
    FAILED
};

typedef struct {
    SPI_HandleTypeDef hspi;
    StatusRegister actualRegister;
    int fixTime :1;
}ExternalFlash;

void FLASH_init(SPI_HandleTypeDef hspi, int fixTime);

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