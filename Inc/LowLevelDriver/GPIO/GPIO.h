#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/GPIO/GPIOErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/GPIO/GPIOStatus.h"

struct GPIO;

typedef void (*GPIO_init)(struct GPIO* instance);

typedef uint8_t (*GPIO_read)(struct GPIO* instance);

typedef void (*GPIO_write)(struct GPIO* instance, uint8_t value);

typedef struct {
  GPIO_init  init;
  GPIO_read read;
  GPIO_write write;

  void* externalHandle;

  uint8_t pinGroup;
  uint8_t pinNumber;
  
  GPIOErrorStatus  errorStatus;
  GPIOStatus       status;
}
GPIO;

extern void GPIO_initDefault(GPIO* instance);

extern int8_t GPIO_readDefault(GPIO* instance);

extern void GPIO_writeDefault(GPIO* instance, uint8_t value);