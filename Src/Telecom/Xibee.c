#include "../../Inc/Devices/Telecom/Xibee.h"

/*uint32_t CRCConverter(uint8_t *data, size_t lenght){
    uint32_t crc = 0x0000FFFF;
    for(size_t i =0; i < lenght; i ++){
        crc ^= data[i];
        for(uint8_t j = 0; j < 8; j++){
            if(crc & 1){
                crc = (crc >> 1) ^ POLYNOMIAL_32B;
            }else {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}*/

void setupBroadCast(Xibee *instance, uint16_t high, uint16_t low){
    //UART send "+++"
    //UART SEND "ATDH high"
    //UART SEND "ATDL low"
    //UART SEND "ATWR"
    //UART SEND "ATCN"
    instance->DH = high;
    instance->DL = low;
}

void setupNetworkID(Xibee *instance, uint16_t id){
    //UART send "+++"
    //UART SEND "ATID id"
    //UART SEND "ATWR"
    //UART SEND "ATCN"
    instance->networkId = id;
}

void sendData(Xibee *instance, uint8_t *data, size_t lenght){
    if(HAL_GetTick() - instance->txTimeStamp < TX_DELAY) return;
    // UART SEND data, lenght
    instance->txTimeStamp = HAL_GetTick();
}

void readData(Xibee *instance, uint8_t *reception, size_t *lenght){
    *lenght = 0;
    if(HAL_GetTick() - instance->txTimeStamp < RX_DELAY) return;

    //UART READ
    //if READING ==0, return lenght set to 0 and skip the timeStamp
    instance->rxTimeStamp = HAL_GetTick();
}