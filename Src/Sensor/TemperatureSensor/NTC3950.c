#include "../../../Inc/Sensor/TemperatureSensor/NTC3950.h"

void NTC3950_init(TemperatureSensor* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
}

void NTC3950_tick(TemperatureSensor* instance, uint32_t timestamp_ms) {
  instance->currentTemperature_adc = *(TemperatureSensorData*)instance->adcChannel->currentValue;
}