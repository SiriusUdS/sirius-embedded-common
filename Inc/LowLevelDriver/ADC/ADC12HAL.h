#pragma once

#include "ADC12.h"

extern void ADCHAL_init(ADC12* instance);

extern int16_t ADCHAL_getValue(ADC12* instance);