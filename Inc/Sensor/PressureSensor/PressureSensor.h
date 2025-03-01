#pragma once

#include "../../LowLevelDriver/ADC/ADC12ChannelHAL.h"

#include "../../../sirius-headers-common/PressureSensor/PressureSensorData.h"
#include "../../../sirius-headers-common/PressureSensor/PressureSensorStatus.h"
#include "../../../sirius-headers-common/PressureSensor/PressureSensorErrorStatus.h"

struct PressureSensor;

typedef void (*PressureSensor_init)(struct PressureSensor* instance);

typedef PressureSensorData (*PressureSensor_readData)(struct PressureSensor* instance);

typedef struct {
  PressureSensor_init       init;
  PressureSensor_readData   readData;

  ADC12Channel* adcChannel;

  PressureSensorErrorStatus errorStatus;
  PressureSensorStatus      status;
}
PressureSensor;

extern void PressureSensor_initDefault(PressureSensor* instance);

extern PressureSensorData PressureSensor_readDataDefault(PressureSensor* instance);