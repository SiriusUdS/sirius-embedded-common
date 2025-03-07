#include "../../../Inc/Sensor/LoadCell/LoadCell.h"

void LoadCell_initDefault(LoadCell* instance) {
  instance->errorStatus.value = 0;
  instance->status.value = 0;
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}

void LoadCell_tickDefault(LoadCell* instance, uint32_t timestamp_ms) {
  instance->errorStatus.bits.defaultFunctionCalled = 1;
}