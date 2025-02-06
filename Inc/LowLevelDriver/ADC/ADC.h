#pragma once

#include "../../../sirius-headers-common/LowLevelDriver/ADC/ADCErrorStatus.h"
#include "../../../sirius-headers-common/LowLevelDriver/ADC/ADCStatus.h"

struct ADC;

typedef void (*ADC_init)(struct ADC* instance);

typedef void (*ADC_readValue)(struct ADC* instance);

typedef int16_t (*ADC_getValue)(struct ADC* instance);

typedef struct {
  int16_t currentValue;

  int16_t disconnectedValue;
  int16_t shortCircuitValue;
  
  ADCErrorStatus  errorStatus;
  ADCStatus       status;
}
ADC;

extern void ADC_initDefault(ADC* instance);

extern void ADC_readValueDefault(ADC* instance);

extern int16_t ADC_getValueDefault(ADC* instance);