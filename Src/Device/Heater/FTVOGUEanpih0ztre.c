#include "../../../Inc/Device/Heater/FTVOGUEanpih0ztre.h"

void FTVOGUEanpih0ztre_init(Heater* instance) {
  instance->setDutyCycle_pct = (Heater_setDutyCycle)FTVOGUEanpih0ztre_setDutyCycle;
  instance->tick = (Heater_tick)FTVOGUEanpih0ztre_tick;
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

void FTVOGUEanpih0ztre_setDutyCycle(Heater* instance, uint8_t dutyCycle_pct) {
  instance->currentDutyCycle_pct = dutyCycle_pct;
}

void FTVOGUEanpih0ztre_tick(Heater* instance, uint32_t timestamp_ms) {
  if (instance->currentDutyCycle_pct == 100) {
    instance->gpio->write(instance->gpio, GPIO_VALUE_HIGH);
    return;
  }

  if (instance->currentDutyCycle_pct == 0) {
    instance->gpio->write(instance->gpio, GPIO_VALUE_LOW);
    return;
  }

  switch(instance->gpio->read(instance->gpio)) {
    case GPIO_VALUE_LOW:
      if (timestamp_ms - instance->lastSwitchTimestamp_ms >= (((uint32_t)instance->period_s * 1000) - ((uint32_t)instance->currentDutyCycle_pct * 100))) {
        instance->lastSwitchTimestamp_ms = timestamp_ms;
        instance->gpio->write(instance->gpio, GPIO_VALUE_HIGH);
      }
      break;
    case GPIO_VALUE_HIGH:
      if (timestamp_ms - instance->lastSwitchTimestamp_ms >= (((uint32_t)instance->period_s * 1000) - (((uint32_t)instance->period_s * 1000) - ((uint32_t)instance->currentDutyCycle_pct * 100)))) {
        instance->lastSwitchTimestamp_ms = timestamp_ms;
        instance->gpio->write(instance->gpio, GPIO_VALUE_LOW);
      }
      break;
    default:
      break;
  }
}