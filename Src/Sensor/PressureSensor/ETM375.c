#include "../../../Inc/Sensor/PressureSensor/ETM375.h"

void ETM375_init(PressureSensor* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

void ETM375_tick(PressureSensor* instance, uint32_t timestamp_ms) {
  instance->currentPressure_adc = *(PressureSensorData*)instance->adcChannel->currentValue;
}