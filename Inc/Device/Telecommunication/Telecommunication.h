#pragma once

#include <stdint.h>

#include "../../../sirius-headers-common/Telecommunication/TelecommunicationStatus.h"
#include "../../../sirius-headers-common/Telecommunication/TelecommunicationErrorStatus.h"
#include "../../../sirius-headers-common/Telecommunication/TelecommunicationState.h"

#include "../../LowLevelDriver/UART/UART.h"
#include "../../LowLevelDriver/UART/UARTHAL.h"
#include "stm32f4xx_hal.h"

struct Telecommunication;

typedef void (*Telecommunication_init)(struct Telecommunication* instance);

typedef void (*Telecommunication_sendData)(struct Telecommunication* instance, uint8_t* data, uint16_t size);

typedef void (*Telecommunication_receiveData)(struct Telecommunication* instance, uint8_t* data, uint16_t size);

typedef void (*Telecommunication_config)(struct Telecommunication* instance);

typedef void (*Telecommunication_tick)(struct Telecommunication* instance, uint32_t timestamp_ms);

typedef struct {
  Telecommunication_init        init;
  Telecommunication_sendData    sendData;
  Telecommunication_receiveData receiveData;
  Telecommunication_config      config;
  Telecommunication_tick        tick;
  
  UART* uart;

  uint8_t state;
  uint32_t timestampTarget_ms;
  uint8_t enableSignalsAmount;

  TelecommunicationErrorStatus  errorStatus;
  TelecommunicationStatus       status;
}
Telecommunication;

void Telecommunication_initDefault(Telecommunication* instance);

void Telecommunication_sendDataDefault(Telecommunication* instance, uint8_t* data, uint16_t size);

void Telecommunication_receiveDataDefault(Telecommunication* instance, uint8_t* data, uint16_t size);

void Telecommunication_configDefault(Telecommunication* instance);

vpod Telecommunication_tickDefault(Telecommunication* instance, uint32_t timestamp_ms);