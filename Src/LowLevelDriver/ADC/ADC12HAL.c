#include "../../../Inc/LowLevelDriver/ADC/ADC12HAL.h"

#include "stm32f4xx_hal.h"

void ADC12HAL_init(ADC12* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
  ADC_HandleTypeDef* adcHandle = (ADC_HandleTypeDef*)instance->externalHandle;

  for (uint8_t i = 0; i < instance->activeChannelsAmt; i++) {
    instance->channels[i].currentValue = &instance->values[i];
  }

  HAL_ADC_Start_DMA(adcHandle, instance->values, (instance->activeChannelsAmt << 1));
}

void ADC12HAL_tick(ADC12* instance) {
  for (uint8_t i = 0; i < instance->activeChannelsAmt; i++) {
    instance->channels[i].tick(&instance->channels[i]);
  }
}