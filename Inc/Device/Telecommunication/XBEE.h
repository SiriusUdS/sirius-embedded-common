#pragma once

#include <stdint.h>

#include "Telecommunication.h"

void XBEE_sendData(Telecommunication* instance, uint8_t* data, uint16_t size);

void XBEE_receiveData(Telecommunication* instance, uint8_t* data, uint16_t size);

void XBEE_setup(Telecommunication* instance);

void XBEE_init(Telecommunication* instance);