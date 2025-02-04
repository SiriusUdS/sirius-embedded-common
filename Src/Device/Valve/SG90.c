#include "../../../Inc/Device/Valve/SG90.h"

static void incrementDutyCycle(Valve* instance);

static void decrementDutyCycle(Valve* instance);

void SG90_init(Valve* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;

  instance->pwm->minDutyCycle_CCR = SG90_PWM_DUTY_CYCLE_MIN_CCR;
  instance->pwm->maxDutyCycle_CCR = SG90_PWM_DUTY_CYCLE_MAX_CCR;

  instance->pwm->currentDutyCycle_CCR = instance->pwm->minDutyCycle_CCR;
}

void SG90_gatherData(Valve* instance) {
  // WAITING FOR PCB TO IMPLEMENT VALVE READING
}

void SG90_tick(Valve* instance) {
  if(instance->pwm->currentDutyCycle_CCR == instance->targetDutyCycle_CCR) {
    instance->status.bits.isClosing = 0;
    instance->status.bits.isOpening = 0;
    return;
  }

  if (instance->pwm->currentDutyCycle_CCR - instance->targetDutyCycle_CCR < 0) {
    incrementDutyCycle(instance);
    instance->status.bits.isClosing = 0;
    instance->status.bits.isOpening = 1;
  }
  else {
    decrementDutyCycle(instance);
    instance->status.bits.isClosing = 1;
    instance->status.bits.isOpening = 0;
  }
}

void SG90_setDutyCycle(Valve* instance, uint32_t dutyCycle_pct) {
  instance->targetDutyCycle_CCR = (int16_t)((dutyCycle_pct * (uint32_t)PWM_DUTY_CYCLE_MAX_CCR) / 100);
}

void incrementDutyCycle(Valve* instance) {
  if (instance->pwm->currentDutyCycle_CCR + SG90_ELAPSED_STEP >= instance->targetDutyCycle_CCR) {
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->targetDutyCycle_CCR);
    instance->pwm->currentDutyCycle_CCR = instance->targetDutyCycle_CCR;
    return;
  }

  if(HAL_GetTick() - instance->pwm->lastDutyCycleChangeTime_ms >= SG90_ELAPSED_DELAY_MS){
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->pwm->currentDutyCycle_CCR + SG90_ELAPSED_STEP);
  }
}

void decrementDutyCycle(Valve* instance) {
  if (instance->pwm->currentDutyCycle_CCR - SG90_ELAPSED_STEP <= instance->targetDutyCycle_CCR) {
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->targetDutyCycle_CCR);
    instance->pwm->currentDutyCycle_CCR = instance->targetDutyCycle_CCR;
    return;
  }

  if(HAL_GetTick() - instance->pwm->lastDutyCycleChangeTime_ms >= SG90_ELAPSED_DELAY_MS){
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->pwm->currentDutyCycle_CCR - SG90_ELAPSED_STEP);
  }
}
