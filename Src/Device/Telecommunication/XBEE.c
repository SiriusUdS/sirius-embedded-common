#include "../../../Inc/Device/Telecommunication/XBee.h"

void XBEE_sendData(Telecommunication* instance, uint8_t* data, uint16_t size) {
  if (instance->state == TELECOMMUNICATION_STATE_ACTIVE) {
    instance->uart->transmit((struct UART*)instance->uart, data, size);
  }
}

void XBEE_receiveData(Telecommunication* instance, uint8_t* data, uint16_t size) {
  if (instance->state == TELECOMMUNICATION_STATE_ACTIVE) {
    instance->uart->receive((struct UART*)instance->uart, data, size);
  }
}

void XBEE_config(Telecommunication* instance){
  instance->enableSignalsAmount = 3;
  instance->state = TELECOMMUNICATION_STATE_CONFIG;
}

void XBEE_init(Telecommunication* instance){
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->state = TELECOMMUNICATION_STATE_INIT;

  instance->enableSignalsAmount = 0;

  instance->receiveData = (Telecommunication_receiveData)XBEE_receiveData;
  instance->sendData = (Telecommunication_sendData)XBEE_sendData;
  instance->config = (Telecommunication_config)XBEE_config;
  instance->tick = (Telecommunication_tick)XBEE_tick;
}

void XBEE_tick(Telecommunication* instance, uint32_t timestamp_ms) {
  switch (instance->state) {
    case TELECOMMUNICATION_STATE_ACTIVE:
      break;
    case TELECOMMUNICATION_STATE_CONFIG:
      if (instance->timestampTarget_ms <= timestamp_ms) {
        instance->timestampTarget_ms += XBEE_ENABLE_TIME_BETWEEN_SIGNALS_MS;
        instance->uart->transmit((struct UART*)instance->uart, XBEE_ENABLE_SIGNAL, sizeof(XBEE_ENABLE_SIGNAL));
        instance->enableSignalsAmount++;
        if (instance->enableSignalsAmount >= XBEE_ENABLE_SIGNAL_AMOUNT) {
          instance->state = TELECOMMUNICATION_STATE_ACTIVE;
        }
      }
      break;
    case TELECOMMUNICATION_STATE_INIT:
    case TELECOMMUNICATION_STATE_INACTIVE:
  default:
    break;
  }
}