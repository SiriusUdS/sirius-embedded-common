#include "../../../Inc/Device/Button/ButtonActiveLow.h"

void ButtonActiveLow_init(Button* instance) {
  instance->tick = (Button_tick)ButtonActiveLow_tick;
  instance->errorStatus.value = 0;
  instance->status.value = 0;

  instance->previousState = GPIO_VALUE_HIGH;
}

void ButtonActiveLow_tick(Button* instance, uint32_t timestamp_ms) {
  if (instance->targetTimestamp_ms <= timestamp_ms) {
    uint8_t state = instance->gpio->read(instance->gpio);
    instance->targetTimestamp_ms = timestamp_ms + instance->delayBetweenReads_ms;

    if (state != instance->previousState) {
      instance->debounceCurrentReadCount = 0;
    }
    else {
      instance->debounceCurrentReadCount++;
    }

    if (instance->debounceCurrentReadCount >= instance->debounceTargetReadCount) {
      if (state == GPIO_VALUE_HIGH) {
        instance->status.bits.isPressed = 0;
      }
      else {
        instance->status.bits.isPressed = 1;
      }
    }

    instance->previousState = state;
  }
}