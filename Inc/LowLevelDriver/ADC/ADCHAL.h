#pragma once

#include "ADC.h"

extern void ADCHAL_init(ADC* instance);

extern void ADCHAL_readValue(ADC* instance);

extern int16_t ADCHAL_getValue(ADC* instance);