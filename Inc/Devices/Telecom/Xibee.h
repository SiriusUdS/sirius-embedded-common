#pragma once
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f411xe.h"

#define POLYNOMIAL_32B 0xEDB88320
#define UART_BAUD 9600
#define DEFAULT_DH 0x0000
#define DEFAULT_DL 0xFFFF
#define DEFAULT_NETWORK_ID 0xFFFF

// NOT REAL VALUES
#define TX_DELAY 50
#define RX_DELAY 50

//uint32_t CRCConverter(uint8_t *data, size_t lenght);

typedef struct{
    uint16_t baudrate;
    uint16_t DH;
    uint16_t DL;
    uint16_t networkId;
    //UART HANDLER
    unsigned long txTimeStamp;
    unsigned long rxTimeStamp;
    
} Xibee;



void setupBroadCast(Xibee *instance, uint16_t high, uint16_t low);

void setupNetworkID(Xibee *instance, uint16_t id);

void sendData(Xibee *instance, uint8_t *data, size_t lenght);

void readData(Xibee *instance, uint8_t *reception, size_t *lenght);