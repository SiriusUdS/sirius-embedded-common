#include "../../../Inc/Device/Telecommunication/XBee.h"

#include "stm32f4xx_hal.h"

static uint8_t XBEE_calculateCRCAPI(XBeeSendAPIPacket packet);

void XBEE_transmit(Telecommunication* instance, uint8_t* data, uint16_t size) {
  if (instance->state == TELECOMMUNICATION_STATE_ACTIVE) {
    XBeeSendAPIPacket api;
    api.bits.del = DELIMITER;
    api.bits.msb = MSB;
    api.bits.lsb = LSB_SEND;
    api.bits.apiFrameType = DEFAULT_API_FRAME_TYPE_SEND;
    api.bits.frameID = 0x01;
    
    
    api.bits.option = 0x00;
    api.bits.broadcast = 0x00;

    uint8_t addr[]=  {0,0,0,0,0,0,0xFF,0xFF};

    for(unsigned int i=0; i < 8; i++){
      api.bits.destAddr64[i] = addr[i];
    }
    api.bits.destAddr16 = 0xFFFE;

    for(uint8_t i = 0; i < size; i++){
      api.bits.data[i] = *(data+i);
    }

    api.bits.checkSum = XBEE_calculateCRCAPI(api);
    instance->uart->transmit((struct UART*)instance->uart, api.data, SEND_PACKET_LENGHT);
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
      uint8_t bit[] = "b";

      HAL_Delay(1000);
      instance->uart->transmit((struct UART*)instance->uart, bit, sizeof(bit));
      HAL_Delay(2500);
      instance->uart->transmit((struct UART*)instance->uart, bit, sizeof(bit));
      HAL_Delay(2500);
      instance->uart->transmit((struct UART*)instance->uart, bit, sizeof(bit));
      HAL_Delay(500);
      instance->state = TELECOMMUNICATION_STATE_ACTIVE;
      __HAL_UART_CLEAR_FLAG((UART_HandleTypeDef*)instance->uart->externalHandle, UART_FLAG_IDLE);
      HAL_UARTEx_ReceiveToIdle_DMA((UART_HandleTypeDef*)instance->uart->externalHandle, instance->receivePacket.data, RECEIVE_PACKET_LENGHT);
      __HAL_UART_CLEAR_FLAG((UART_HandleTypeDef*)instance->uart->externalHandle, UART_FLAG_IDLE);
      /*if (instance->timestampTarget_ms <= timestamp_ms) {
        uint8_t bit[] = "b";
        instance->timestampTarget_ms += XBEE_ENABLE_TIME_BETWEEN_SIGNALS_MS;
        instance->uart->transmit((struct UART*)instance->uart, bit, sizeof(bit));
        instance->enableSignalsAmount++;
        if (instance->enableSignalsAmount >= XBEE_ENABLE_SIGNAL_AMOUNT) {
          instance->state = TELECOMMUNICATION_STATE_ACTIVE;
        }
      }*/
      break;
    case TELECOMMUNICATION_STATE_INIT:
    case TELECOMMUNICATION_STATE_INACTIVE:
  default:
    break;
  }
}

uint8_t XBEE_calculateCRCAPI(XBeeSendAPIPacket packet)
{
    uint64_t calc = 0;

    for(unsigned int i=0; i < LSB_SEND-14; i++){
      calc += packet.bits.data[i];
    }
    calc += packet.bits.apiFrameType;
    calc += packet.bits.broadcast;
    calc += packet.bits.destAddr16;

    uint64_t addr64 = 0;
    for (int i = 0; i < 8; i++) {
        addr64 |= ((uint64_t)packet.bits.destAddr64[i]) << (8 * (7 - i)); // Big-endian
    }
    calc += addr64;
    calc += packet.bits.frameID;
    calc += packet.bits.option;

    return (calc & 0xFF);
}