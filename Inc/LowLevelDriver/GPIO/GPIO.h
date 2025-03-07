#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/GPIO/GPIOErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/GPIO/GPIOStatus.h"

struct GPIO;

typedef enum {
  GPIO_MODE_INPUT,
  GPIO_MODE_OUTPUT
}
GPIOMode;

typedef enum {
  GPIO_NO_PULL,
  GPIO_PULL_DOWN,
  GPIO_PULL_UP
}
GPIOPullMode;

typedef enum {
  GPIO_HIGH,
  GPIO_LOW
}
GPIOValue;

typedef void (*GPIO_init)(struct GPIO* instance);

typedef uint8_t (*GPIO_read)(struct GPIO* instance);

typedef void (*GPIO_write)(struct GPIO* instance, uint8_t value);

typedef struct {
  GPIO_init  init;
  GPIO_read read;
  GPIO_write write;

  void* externalHandle;

  uint8_t currentValue;

  GPIOMode mode;
  GPIOPullMode pullMode;
  
  uint8_t  pinGroup;
  uint8_t  pinNumber;
  
  GPIOErrorStatus  errorStatus;
  GPIOStatus       status;
}
GPIO;

extern void GPIO_initDefault(GPIO* instance);

extern int8_t GPIO_readDefault(GPIO* instance);

extern void GPIO_writeDefault(GPIO* instance, uint8_t value);