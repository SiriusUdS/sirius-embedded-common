#include "../../../Inc/LowLevelDriver/ADC/ADC12HAL.h"

#include "stm32f4xx_hal.h"

void ADCHAL_init(ADC12* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;

  instance->currentValue = 0;
}

int16_t ADCHAL_getValue(ADC12* instance) {
  ADC_ChannelConfTypeDef adcConfig = {0};
  ADC_HandleTypeDef* adcHandle = (ADC_HandleTypeDef*)instance->externalHandle;

  adcConfig.Channel = instance->channel;
  adcConfig.Rank = instance->rank;
  adcConfig.SamplingTime = instance->sampleTime_adcClockCyles;

  HAL_ADC_ConfigChannel(adcHandle, &adcConfig);
  HAL_ADC_PollForConversion(adcHandle, 50);

  return (int16_t)HAL_ADC_GetValue(adcHandle);
}