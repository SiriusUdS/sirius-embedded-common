#include "../../../Inc/Device/Telecommunication/XBee.h"

void XBEE_sendData(Telecommunication* instance, uint8_t* data, uint16_t size){
  instance->uart->transmit((struct UART*)instance->uart, data, size);
}

void XBEE_receiveData(Telecommunication* instance, uint8_t* data, uint16_t size){
  instance->uart->receive((struct UART*)instance->uart, data, size);
}

void XBEE_config(Telecommunication* instance){
  uint8_t bit [] = "b";
  instance->uart->transmit((struct UART*)instance->uart, bit, sizeof(bit));
  HAL_Delay(2500);
  instance->uart->transmit((struct UART*)instance->uart, bit, sizeof(bit));
  HAL_Delay(2500);
  instance->uart->transmit((struct UART*)instance->uart, bit, sizeof(bit));
  HAL_Delay(500);
}

void XBEE_init(Telecommunication* instance){
  instance->receiveData = (Telecommunication_receiveData)XBEE_receiveData;
  instance->sendData = (Telecommunication_sendData)XBEE_sendData;
  instance->config = (Telecommunication_config)XBEE_config;
}