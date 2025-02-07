#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/ADC/ADCErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/ADC/ADCStatus.h"

struct ADC12;

typedef void (*ADC_init)(struct ADC12* instance);

typedef int16_t (*ADC_getValue)(struct ADC12* instance);

typedef struct {
  ADC_init      init;
  ADC_getValue  getValue;

  void* externalHandle;
  
  uint32_t channel;
  uint32_t rank;
  uint32_t sampleTime_adcClockCyles;

  int16_t currentValue;
  int16_t disconnectedValue;
  int16_t shortCircuitValue;
  
  ADCErrorStatus  errorStatus;
  ADCStatus       status;
}
ADC12;

extern void ADC_initDefault(ADC12* instance);

extern int16_t ADC_getValueDefault(ADC12* instance);