#include "../../../Inc/Devices/Valve/Valve.h"

void Valve_initDefault(Valve* instance) {
  instance->status.value = 0;
  instance->status.bits.invalidFunctionPointer = 1;
}

void Valve_gatherDataDefault(Valve* instance) {
  instance->status.bits.invalidFunctionPointer = 1;
}

void Valve_setStateDefault(Valve* instance, ValveState state) {
  instance->status.bits.invalidFunctionPointer = 1;
}