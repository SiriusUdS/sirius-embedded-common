#include "../../../Inc/Device/Button/ButtonActiveHigh.h"

void ButtonActiveHigh_init(Button* instance) {
  instance->tick = (Button_tick)ButtonActiveHigh_tick;
  instance->errorStatus.value = 0;
  instance->status.value = 0;

  instance->previousState = GPIO_VALUE_LOW;
}

void ButtonActiveHigh_tick(Button* instance, uint32_t timestamp_ms) {
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
      instance->status.bits.isPressed = state;
      instance->debounceCurrentReadCount = 0;
    }

    instance->previousState = state;
  }
}