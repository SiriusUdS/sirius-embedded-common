#include "../../../Inc/Sensor/PressureSensor/ETM375.h"

void ETM375_init(PressureSensor* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
}

void ETM375_gatherData(PressureSensor* instance) {
  PressureSensorData currentData = {0};
  
  currentData.rawPressure = *instance->adcChannel->currentValue;
  return currentData;
}