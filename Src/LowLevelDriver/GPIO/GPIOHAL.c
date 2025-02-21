#include "../../../Inc/LowLevelDriver/GPIO/GPIOHAL.h"

#include "stm32f4xx_hal.h"

void GPIOHAL_init(GPIO* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

int8_t GPIOHAL_read(GPIO* instance) {
  return HAL_GPIO_ReadPin(instance->pinGroup, instance->pinNumber);
}

void GPIOHAL_write(GPIO* instance, uint8_t value) {
  HAL_GPIO_WritePin(instance->pinGroup, instance->pinNumber, (GPIO_PinState)value);
}