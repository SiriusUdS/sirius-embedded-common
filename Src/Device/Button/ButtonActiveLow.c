#include "../../../Inc/Device/Button/ButtonActiveLow.h"

void ButtonActiveLow_init(Button* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

void ButtonActiveLow_tick(Button* instance, uint32_t timestamp_ms) {
  instance->status.bits.isPressed = instance->gpio->read(instance->gpio);
}