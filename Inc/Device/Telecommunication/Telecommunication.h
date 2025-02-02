#pragma once

#include <stdint.h>

#include "../../../sirius-headers-common/Telecommunication/TelecommunicationStatus.h"
#include "../../../sirius-headers-common/Telecommunication/TelecommunicationErrorStatus.h"

struct Telecommunication;

typedef void (*Telecommunication_init)(struct Telecommunication* instance);

typedef void (*Telecommunication_sendData)(struct Telecommunication* instance, uint8_t* data);

typedef void (*Telecommunication_receiveData)(struct Telecommunication* instance, uint8_t* data);

typedef struct {
  Telecommunication_init        init;
  Telecommunication_sendData    sendData;
  Telecommunication_receiveData receiveData;

  TelecommunicationErrorStatus  errorStatus;
  TelecommunicationStatus       status;
}
Telecommunication;