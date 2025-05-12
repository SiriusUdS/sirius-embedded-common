#pragma once

#include <stdint.h>

#include "../../../sirius-headers-common/Telecommunication/TelecommunicationStatus.h"
#include "../../../sirius-headers-common/Telecommunication/TelecommunicationErrorStatus.h"

#include "../../LowLevelDriver/UART/UART.h"
#include "../../LowLevelDriver/UART/UARTHAL.h"
#include "stm32f4xx_hal.h"

struct Telecommunication;

typedef void (*Telecommunication_init)(struct Telecommunication* instance);

typedef void (*Telecommunication_sendData)(struct Telecommunication* instance, uint8_t* data, uint16_t size);

typedef void (*Telecommunication_receiveData)(struct Telecommunication* instance, uint8_t* data, uint16_t size);

typedef void (*Telecommunication_config)(struct Telecommunication* instance);

typedef struct {
  Telecommunication_init        init;
  Telecommunication_sendData    sendData;
  Telecommunication_receiveData receiveData;
  Telecommunication_config      config;
  
  UART* uart;

  TelecommunicationErrorStatus  errorStatus;
  TelecommunicationStatus       status;
}
Telecommunication;

void TELECOM_init(Telecommunication* instance);

void TELECOM_sendData(Telecommunication* instance, uint8_t* data, uint16_t size);

void TELECOM_receiveData(Telecommunication* instance, uint8_t* data, uint16_t size);

void TELECOM_config(Telecommunication* instance);