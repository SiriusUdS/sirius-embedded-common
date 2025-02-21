#pragma once

#include "../../LowLevelDriver/ADC/ADC12HAL.h"
#include "../../../sirius-headers-common/TemperatureSensor/TemperatureSensorStatus.h"
#include "../../../sirius-headers-common/TemperatureSensor/TemperatureSensorErrorStatus.h"

typedef void (*TemperatureSensor_init)(struct TemperatureSensor* instance);

typedef int16_t (*TemperatureSensor_readData)(struct TemperatureSensor* instance);

typedef struct {
  TemperatureSensor_init     init;
  TemperatureSensor_readData readData;

  ADC12* adc;

  TemperatureSensorErrorStatus errorStatus;
  TemperatureSensorStatus      status;
}
TemperatureSensor;

extern void TemperatureSensor_initDefault(TemperatureSensor* instance);

extern int16_t TemperatureSensor_readDataDefault(TemperatureSensor* instance);
