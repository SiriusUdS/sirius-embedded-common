#pragma once

#include "ADC12.h"

extern void ADC12HAL_init(ADC12* instance);

extern int16_t ADC12HAL_getValue(ADC12* instance);