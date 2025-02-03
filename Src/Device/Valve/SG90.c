#include "../../../Inc/Device/Valve/SG90.h"


void SG90_init(Valve* instance) {
    instance->status.value = 0;
    instance->errorStatus.value = 0;

    
}

void SG90_gatherData(Valve* instance) {

}

void SG90_setDutyCycle(Valve* instance, uint8_t dutyCycle_pct) {

}
