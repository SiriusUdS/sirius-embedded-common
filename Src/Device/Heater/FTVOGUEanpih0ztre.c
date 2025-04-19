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
    if (instance->gpio->currentValue == GPIO_VALUE_LOW) {
      instance->gpio->write(instance->gpio, GPIO_VALUE_HIGH);
    }
    return;
  }

  if (timestamp_ms - instance->lastSwitchTimestamp_ms <= (uint32_t)instance->period_s * ((uint32_t)10 * (uint32_t)instance->currentDutyCycle_pct)) {

  }
}