#include "../../../Inc/Device/Valve/HBL388.h"

static void incrementDutyCycle(Valve* instance);

static void decrementDutyCycle(Valve* instance);

static uint8_t isMovementCompleted(Valve* instance);

void HBL388_init(Valve* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;

  instance->pwm->minDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MIN_CCR;
  instance->pwm->maxDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MAX_CCR;
  instance->pwm->prescaler = HBL388_PSC;
  instance->pwm->autoReload = HBL388_ARR;

  instance->pwm->currentDutyCycle_CCR = instance->pwm->minDutyCycle_CCR;
}

void HBL388_close(Valve* instance, uint32_t timestamp_ms) {
  instance->targetDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MIN_CCR;
  instance->pwm->setDutyCycle(instance->pwm, HBL388_PWM_DUTY_CYCLE_MIN_CCR);
  instance->lastDutyCycleChangeTimestamp_ms = timestamp_ms;
}

void HBL388_open(Valve* instance, uint32_t timestamp_ms) {
  instance->targetDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MAX_CCR;
  instance->pwm->setDutyCycle(instance->pwm, HBL388_PWM_DUTY_CYCLE_MAX_CCR);
  instance->lastDutyCycleChangeTimestamp_ms = timestamp_ms;
}

void HBL388_tick(Valve* instance, uint32_t timestamp_ms) {
  if (instance->adjustmentsCount >= instance->maxAdjustmentsCount) {
    instance->errorStatus.bits.exceededMaxAdjustments = 1;
  }

  switch (instance->currentState) {
    case VALVE_CLOSED:
    case VALVE_OPENED:
      break;
    case VALVE_CLOSING:
      if (isMovementCompleted) {
        instance->currentState = VALVE_CLOSED;
        instance->adjustmentsCount = 0;
      }
      else if (instance->lastDutyCycleChangeTimestamp_ms + instance->slowestExpectedMoveTime_ms < timestamp_ms) {
        decrementDutyCycle(instance);
        instance->adjustmentsCount++;
      }
      break;
    case VALVE_OPENING:
      if (isMovementCompleted) {
        instance->currentState = VALVE_OPENED;
        instance->adjustmentsCount = 0;
      }
      else if (instance->lastDutyCycleChangeTimestamp_ms + instance->slowestExpectedMoveTime_ms < timestamp_ms) {
        incrementDutyCycle(instance);
        instance->adjustmentsCount++;
      }
      break;
    case VALVE_UNKNOWN:
    default:
      instance->errorStatus.bits.invalidState = 1;
      break;
  }
}

// Unused for now, but way be used with tests
void HBL388_setDutyCycle(Valve* instance, uint32_t dutyCycle_pct) {
  instance->targetDutyCycle_CCR = (int16_t)((dutyCycle_pct * (uint32_t)HBL388_PWM_DUTY_CYCLE_MAX_CCR) / 100);
}

void incrementDutyCycle(Valve* instance) {
  if(HAL_GetTick() - instance->pwm->lastDutyCycleChangeTimestamp_ms >= HBL388_ELAPSED_DELAY_MS){
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->pwm->currentDutyCycle_CCR + HBL388_STEP);
  }
}

void decrementDutyCycle(Valve* instance) {
  if(HAL_GetTick() - instance->pwm->lastDutyCycleChangeTimestamp_ms >= HBL388_ELAPSED_DELAY_MS){
    instance->pwm->setDutyCycle((struct PWM*)instance->pwm, instance->pwm->currentDutyCycle_CCR - HBL388_STEP);
  }
}

uint8_t isMovementCompleted(Valve* instance) {
  // Check if switch has been triggered
  // return 1 if completed
  // return 0 if not completed
}