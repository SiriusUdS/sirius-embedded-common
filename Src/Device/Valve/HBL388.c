#include "../../../Inc/Device/Valve/HBL388.h"

static void incrementDutyCycle(Valve* instance);

static void decrementDutyCycle(Valve* instance);

void HBL388_init(Valve* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;

  instance->pwm->minDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MIN_CCR;
  instance->pwm->maxDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MAX_CCR;
  instance->pwm->prescaler = HBL388_PSC;
  instance->pwm->autoReload = HBL388_ARR;

  instance->pwm->currentDutyCycle_CCR = instance->pwm->minDutyCycle_CCR;
}

void HBL388_gatherData(Valve* instance) {
  // WAITING FOR PCB TO IMPLEMENT VALVE READING
}

void HBL388_close(Valve* instance) {
  instance->targetDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MIN_CCR;
  instance->pwm->setDutyCycle(instance->pwm, HBL388_PWM_DUTY_CYCLE_MIN_CCR);
}

void HBL388_open(Valve* instance) {
  instance->targetDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MAX_CCR;
  instance->pwm->setDutyCycle(instance->pwm, HBL388_PWM_DUTY_CYCLE_MAX_CCR);
}

void HBL388_tick(Valve* instance) {
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

void HBL388_setDutyCycle(Valve* instance, uint32_t dutyCycle_pct) {
  instance->targetDutyCycle_CCR = (int16_t)((dutyCycle_pct * (uint32_t)HBL388_PWM_DUTY_CYCLE_MAX_CCR) / 100);
}

void incrementDutyCycle(Valve* instance) {
  if (instance->pwm->currentDutyCycle_CCR + HBL388_STEP >= instance->targetDutyCycle_CCR) {
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->targetDutyCycle_CCR);
    instance->pwm->currentDutyCycle_CCR = instance->targetDutyCycle_CCR;
    return;
  }

  if(HAL_GetTick() - instance->pwm->lastDutyCycleChangeTimestamp_ms >= HBL388_ELAPSED_DELAY_MS){
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->pwm->currentDutyCycle_CCR + HBL388_STEP);
  }
}

void decrementDutyCycle(Valve* instance) {
  if (instance->pwm->currentDutyCycle_CCR - HBL388_STEP <= instance->targetDutyCycle_CCR) {
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->targetDutyCycle_CCR);
    instance->pwm->currentDutyCycle_CCR = instance->targetDutyCycle_CCR;
    return;
  }

  if(HAL_GetTick() - instance->pwm->lastDutyCycleChangeTimestamp_ms >= HBL388_ELAPSED_DELAY_MS){
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->pwm->currentDutyCycle_CCR - HBL388_ELAPSED_STEP);
  }
}