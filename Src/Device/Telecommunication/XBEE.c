#include "../../../Inc/Device/Telecommunication/XBee.h"

#include "stm32f4xx_hal.h"

void XBEE_transmit(Telecommunication* instance, uint8_t* data, uint16_t size) {
  if (instance->state == TELECOMMUNICATION_STATE_ACTIVE) {
    instance->uart->transmit((struct UART*)instance->uart, data, size);
  }
}

void XBEE_receive(Telecommunication* instance, uint8_t* data, uint16_t size) {
  if (instance->state == TELECOMMUNICATION_STATE_ACTIVE) {
    instance->uart->receive((struct UART*)instance->uart, data, size);
  }
}

void XBEE_config(Telecommunication* instance){
  instance->enableSignalsAmount = 0;
  instance->state = TELECOMMUNICATION_STATE_CONFIG;
}

void XBEE_init(Telecommunication* instance){
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->state = TELECOMMUNICATION_STATE_INIT;

  instance->enableSignalsAmount = 0;

  instance->receiveData = (Telecommunication_receive)XBEE_receive;
  instance->sendData = (Telecommunication_transmit)XBEE_transmit;
  instance->config = (Telecommunication_config)XBEE_config;
  instance->tick = (Telecommunication_tick)XBEE_tick;
}

void XBEE_tick(Telecommunication* instance, uint32_t timestamp_ms) {
  switch (instance->state) {
    case TELECOMMUNICATION_STATE_ACTIVE:
      break;
    case TELECOMMUNICATION_STATE_CONFIG:
      break;
    case TELECOMMUNICATION_STATE_INIT:
    case TELECOMMUNICATION_STATE_INACTIVE:
  default:
    break;
  }
}