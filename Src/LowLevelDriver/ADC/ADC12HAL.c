#include "../../../Inc/LowLevelDriver/ADC/ADC12HAL.h"

#include "stm32f4xx_hal.h"

void ADC12HAL_init(ADC12* instance, ADCBuffer* dmaBuffer, uint8_t activeChannelsAmt) {
  instance->tick = (ADC12_tick)ADC12HAL_tick;
  instance->errorStatus.value = 0;
  instance->status.value = 0;
  ADC_HandleTypeDef* adcHandle = (ADC_HandleTypeDef*)instance->externalHandle;
  instance->activeChannelsAmt = activeChannelsAmt;

  for (uint8_t i = 0; i < instance->activeChannelsAmt; i++) {
    instance->channels[i].currentValue = &instance->values[i];
    instance->channels[i].externalHandle = instance->externalHandle; 
  }

  HAL_ADC_Start_DMA(adcHandle, dmaBuffer->values, sizeof(dmaBuffer->values) / sizeof(uint16_t));
}

void ADC12HAL_tick(ADC12* instance) {
  for (uint8_t i = 0; i < instance->activeChannelsAmt; i++) {
    instance->channels[i].tick(&instance->channels[i]);
  }
}