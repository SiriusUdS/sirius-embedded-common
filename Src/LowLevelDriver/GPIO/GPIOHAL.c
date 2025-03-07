#include "../../../Inc/LowLevelDriver/GPIO/GPIOHAL.h"

#include "stm32f4xx_hal.h"

void GPIOHAL_init(GPIO* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

GPIOValue GPIOHAL_read(GPIO* instance) {
  instance->currentValue = (GPIOValue)HAL_GPIO_ReadPin(instance->pinGroup, instance->pinNumber);
  return instance->currentValue;
}

void GPIOHAL_write(GPIO* instance, GPIOValue value) {
  instance->currentValue = value;
  HAL_GPIO_WritePin(instance->pinGroup, instance->pinNumber, (GPIO_PinState)instance->currentValue);
}