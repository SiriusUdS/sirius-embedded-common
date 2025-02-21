#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/UART/UARTErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/UART/UARTStatus.h"

#define UART_COMMUNICATION_TIMEOUT_MS 50

struct UART;

typedef void (*UART_init)(struct UART* instance);

typedef void (*UART_sendData)(struct UART* instance, uint8_t* data, uint16_t size);

typedef void (*UART_receiveData)(struct UART* instance, uint8_t* data, uint16_t size);

typedef struct {
  UART_init        init;
  UART_sendData    sendData;
  UART_receiveData receiveData;

  void* externalHandle;
  
  UARTErrorStatus  errorStatus;
  UARTStatus       status;
}
UART;

extern void UART_initDefault(UART* instance);

extern void UART_sendDataDefault(UART* instance, uint8_t* data, uint16_t size);

extern void UART_receiveDataDefault(UART* instance, uint8_t* data, uint16_t size);