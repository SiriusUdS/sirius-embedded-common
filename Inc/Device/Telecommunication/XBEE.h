#pragma once

#include "Telecommunication.h"

#define XBEE_ENABLE_SIGNAL "b"
#define XBEE_ENABLE_TIME_BETWEEN_SIGNALS_MS (uint8_t)50
#define XBEE_ENABLE_SIGNAL_AMOUNT (uint8_t)0x03

void XBEE_sendData(Telecommunication* instance, uint8_t* data, uint16_t size);

void XBEE_receiveData(Telecommunication* instance, uint8_t* data, uint16_t size);

void XBEE_config(Telecommunication* instance);

void XBEE_init(Telecommunication* instance);