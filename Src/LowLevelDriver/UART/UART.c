#include "../../../Inc/LowLevelDriver/UART/UART.h"

void UART_initDefault(UART* instance) {
  instance->sendData = (UART_sendData)UART_sendDataDefault;
  instance->receiveData = (UART_receiveData)UART_receiveDataDefault;
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void UART_sendDataDefault(UART* instance, uint8_t* data, uint16_t size) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void UART_receiveDataDefault(UART* instance, uint8_t* data, uint16_t size) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}