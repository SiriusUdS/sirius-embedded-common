#pragma once

#include "../../../sirius-headers-common/Button/ButtonErrorStatus.h"
#include "../../../sirius-headers-common/Button/ButtonStatus.h"

#include "../../LowLevelDriver/GPIO/GPIO.h"

struct Button;


typedef void (*Button_init)(struct Button* instance);

typedef void (*Button_tick)(struct Button* instance, uint32_t timestamp_ms);

typedef struct {
  Button_init   init;
  Button_tick   tick;

  GPIO* gpio;

  uint8_t debounceCurrentReadCount;
  uint8_t debounceTargetReadCount;

  uint32_t targetTimestamp_ms;
  uint32_t delayBetweenReads_ms;

  uint8_t previousState;

  ButtonErrorStatus errorStatus;
  ButtonStatus      status;
}
Button;

extern void Button_initDefault(Button* instance);

extern void Button_tickDefault(Button* instance, uint32_t timestamp_ms);