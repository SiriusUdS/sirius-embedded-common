#pragma once

#include "ADC12.h"

extern void ADC12HAL_init(ADC12* instance, uint16_t* buffer, uint16_t bufferSize_byte, uint8_t activeChannelsAmt);

extern void ADC12HAL_tick(ADC12* instance);