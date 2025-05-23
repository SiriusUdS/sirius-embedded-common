#include "../../../Inc/Device/Button/ButtonActiveLow.h"

void ButtonActiveLow_init(Button* instance) {
  instance->tick = (Button_tick)ButtonActiveLow_tick;
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

void ButtonActiveLow_tick(Button* instance, uint32_t timestamp_ms) {
  if(instance->gpio->read(instance->gpio) == GPIO_VALUE_HIGH){
    instance->status.bits.isPressed = GPIO_VALUE_LOW;
  }
  else{
    instance->status.bits.isPressed = GPIO_VALUE_HIGH;
  }

}