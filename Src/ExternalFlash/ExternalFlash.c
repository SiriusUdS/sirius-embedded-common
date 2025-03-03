#include "../../Inc/Devices/Storage/ExternalFlash/ExternalFlash.h"

static volatile ExternalFlash flash;

static void enableWrite();

static void disableWrite();

static void getRegister();

void FLASH_init(SPI_HandleTypeDef hspi, int fixTime){
    flash.hspi = hspi;
    flash.fixTime = fixTime;
}

int FLASH_write(uint8_t* addr, uint8_t* din, size_t size){
    if(size < 4) return FAILED;
    enableWrite();
    while(flash.actualRegister.wel == 0){
        getRegister();
        HAL_Delay(1);
    }

    size_t nbPackage = size/PCKG_SIZE_BYTE;

    int isEven = 1;
    if((size % 2) != 0){
        size++;
        nbPackage++;
        isEven = 0;
    }

    // first pckg

    size_t cursor = 2;
    uint8_t header[] = {AAI, *(addr), *(addr+1), *(addr+2), *(din), *(din+1)};
    HAL_SPI_Transmit(&flash.hspi, header, 6, 500);
    if(flash.fixTime){
        HAL_Delay(T_BP_US);
        // TODO : MODIFY HAL_DELAY TO DELAY US
    }else{
        getRegister();
        while(flash.actualRegister.busy){
            getRegister();
            HAL_Delay(1);
        }
    }

    size_t cursor = 0;
    for(size_t i = 0; i < nbPackage+1; i++){
        uint8_t pckg[] = {AAI, *(din+ cursor++), *(din+ cursor++)};
        HAL_SPI_Transmit(&flash.hspi, pckg, 3, 500);

        if(flash.fixTime){
            HAL_Delay(T_BP_US);
            // TODO : SEE LINE 40
        }else{
            getRegister();
            while(flash.actualRegister.busy){
                getRegister();
                HAL_Delay(1);
            }
        }
        
    }

    disableWrite();

    return SUCCESS;

}
int FLASH_read(uint8_t* addr, uint8_t* dout, size_t size){
    if(size < 4) return FAILED;

    uint8_t header[] = {RD, *(addr), *(addr+1), *(addr+2)};
    HAL_SPI_Transmit(&flash.hspi, header, 4, 500);
    HAL_SPI_Receive(&flash.hspi, dout, size, 500);
    return SUCCESS;
}

int FLASH_ERASE(uint8_t* addr){
    uint8_t header[] = {ERASE, *(addr), *(addr+1), *(addr+2)};
    HAL_SPI_Transmit(&flash.hspi, header, 4, 500);
    return SUCCESS;
}

void FLASH_readStatusRegister(StatusRegister* reg){
    getRegister();
    reg = &flash.actualRegister;
}

void enableWrite(){
    uint8_t body[] = {WREN};
    HAL_SPI_Transmit(&flash.hspi, body, 1, 500);
    getRegister();
}

void disableWrite(){
    uint8_t body[] = {WRDI};
    HAL_SPI_Transmit(&flash.hspi, body, 1, 500);
    getRegister();
}

void getRegister(){
    uint8_t body[] = {RDSR};
    HAL_SPI_Transmit(&flash.hspi, body, 1, 500);
    HAL_SPI_Receive(&flash.hspi, body, 1, 500);
    uint8_t temp[8];
    for(unsigned int i=0; i < 8; i++){
        temp[i] = (body[0] & (1 << i)) ? 1 :0; 
    }
    flash.actualRegister.busy = temp[0];
    flash.actualRegister.wel = temp[1];
    flash.actualRegister.BP0 = temp[2];
    flash.actualRegister.BP1 = temp[3];
    flash.actualRegister.BP2 = temp[4];
    flash.actualRegister.BP3 = temp[5];
    flash.actualRegister.aai = temp[6];
    flash.actualRegister.bpl = temp[7];
}