#include "../../../Inc/Device/Valve/HBL388.h"

static void incrementDutyCycle(Valve* instance);

static void decrementDutyCycle(Valve* instance);

static ValveMovementCompleted isMovementCompleted(Valve* instance);

void HBL388_init(Valve* instance) {
  instance->setIdle = (Valve_setIdle)HBL388_setIdle;
  instance->close = (Valve_close)HBL388_close;
  instance->open = (Valve_close)HBL388_open;
  instance->tick = (Valve_tick)HBL388_tick;
  instance->setDutyCycle = (Valve_setPositionOpened)HBL388_setOpenedPosition_pct;

  instance->status.value = 0;
  instance->errorStatus.value = 0;
  instance->currentPositionOpened_pct = 0;
  instance->isReversed = 0;
  instance->lastDutyCycleChangeTimestamp_ms = 0;

  instance->pwm->minDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MIN_CCR;
  instance->pwm->maxDutyCycle_CCR = HBL388_PWM_DUTY_CYCLE_MAX_CCR;
  instance->pwm->prescaler = HBL388_PSC;
  instance->pwm->autoReload = HBL388_ARR;

  instance->pwm->currentDutyCycle_CCR = instance->pwm->minDutyCycle_CCR;
}

void HBL388_setIdle(Valve* instance) {
  instance->pwm->setDutyCycle(instance->pwm, 0);
  instance->status.bits.isIdle = 1;
}

void HBL388_close(Valve* instance, uint32_t timestamp_ms) {
  instance->pwm->setDutyCycle(instance->pwm, (HBL388_ARR * (uint32_t)instance->closeDutyCycle_pct) / 100);
  instance->lastDutyCycleChangeTimestamp_ms = timestamp_ms;
  instance->currentState = VALVE_STATE_CLOSING;
  instance->status.bits.isIdle = 0;
  instance->currentPositionOpened_pct = 0;
  instance->lastDutyCycleChangeTimestamp_ms = timestamp_ms;
}

void HBL388_open(Valve* instance, uint32_t timestamp_ms) {
  instance->pwm->setDutyCycle(instance->pwm, (HBL388_ARR * (uint32_t)instance->openDutyCycle_pct) / 100);
  instance->lastDutyCycleChangeTimestamp_ms = timestamp_ms;
  instance->currentState = VALVE_STATE_OPENING;
  instance->status.bits.isIdle = 0;
  instance->currentPositionOpened_pct = 100;
  instance->lastDutyCycleChangeTimestamp_ms = timestamp_ms;
}

void HBL388_tick(Valve* instance, uint32_t timestamp_ms) {
  if (instance->adjustmentsCount >= instance->maxAdjustmentsCount) {
    instance->errorStatus.bits.exceededMaxAdjustments = 1;
  }

  instance->heatpad->tick(instance->heatpad, timestamp_ms);

  switch (instance->currentState) {
    case VALVE_STATE_CLOSED:
    case VALVE_STATE_OPENED:
      break;
    case VALVE_STATE_CLOSING:
      if (isMovementCompleted(instance) == VALVE_MOVEMENT_COMPLETED) {
        instance->currentState = VALVE_STATE_CLOSED;
        instance->setIdle(instance);
        instance->adjustmentsCount = 0;
      }
      /*else if (instance->lastDutyCycleChangeTimestamp_ms + instance->slowestExpectedMoveTime_ms < timestamp_ms) {
        decrementDutyCycle(instance);
        instance->adjustmentsCount++;
      }*/
      break;
    case VALVE_STATE_OPENING:
      if (isMovementCompleted(instance) == VALVE_MOVEMENT_COMPLETED) {
        instance->currentState = VALVE_STATE_OPENED;
        instance->setIdle(instance);
        instance->adjustmentsCount = 0;
      }
      /*else if (instance->lastDutyCycleChangeTimestamp_ms + instance->slowestExpectedMoveTime_ms < timestamp_ms) {
        incrementDutyCycle(instance);
        instance->adjustmentsCount++;
      }*/
      break;
    case VALVE_STATE_UNKNOWN:
    default:
      instance->currentState = VALVE_STATE_UNKNOWN;
      instance->errorStatus.bits.invalidState = 1;
      break;
  }

  if (timestamp_ms - instance->lastDutyCycleChangeTimestamp_ms >= VALVE_MOVEMENT_MAX_DURATION_MS) {
    instance->setIdle(instance);
  }
}

void HBL388_setOpenedPosition_pct(Valve* instance, uint32_t dutyCycle_pct, uint32_t timestamp_ms) {
  if (dutyCycle_pct >= 100) {
    HBL388_open(instance, timestamp_ms);
  } else if (dutyCycle_pct <= 0) {
    HBL388_close(instance, timestamp_ms);
  }
  instance->currentPositionOpened_pct = dutyCycle_pct;
  instance->lastDutyCycleChangeTimestamp_ms = timestamp_ms;
  const uint32_t CLOSED_CCR = (HBL388_ARR * (uint32_t)instance->closeDutyCycle_pct) / 100;
  instance->pwm->setDutyCycle((struct PWM*)instance->pwm, (int16_t)(CLOSED_CCR + ((dutyCycle_pct * ((float)((float)instance->openDutyCycle_pct - (float)instance->closeDutyCycle_pct) / 100.0f)) * (uint32_t)HBL388_PWM_DUTY_CYCLE_MAX_CCR) / (uint32_t)100));
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

ValveMovementCompleted isMovementCompleted(Valve* instance) {
  switch (instance->currentState) {
    case VALVE_STATE_CLOSED:
    case VALVE_STATE_OPENED:
      return VALVE_MOVEMENT_COMPLETED;
    case VALVE_STATE_CLOSING:
      if (instance->gpio[VALVE_GPIO_CLOSED_INDEX]->read(instance->gpio[VALVE_GPIO_CLOSED_INDEX]) == GPIO_VALUE_LOW &&
          instance->gpio[VALVE_GPIO_OPENED_INDEX]->read(instance->gpio[VALVE_GPIO_OPENED_INDEX]) == GPIO_VALUE_HIGH) {
        return VALVE_MOVEMENT_COMPLETED;
      }
      return VALVE_MOVEMENT_NOT_COMPLETED;
    case VALVE_STATE_OPENING:
      if (instance->gpio[VALVE_GPIO_OPENED_INDEX]->read(instance->gpio[VALVE_GPIO_OPENED_INDEX]) == GPIO_VALUE_LOW &&
          instance->gpio[VALVE_GPIO_CLOSED_INDEX]->read(instance->gpio[VALVE_GPIO_CLOSED_INDEX]) == GPIO_VALUE_HIGH) {
        return VALVE_MOVEMENT_COMPLETED;
      }
      return VALVE_MOVEMENT_NOT_COMPLETED;
    case VALVE_STATE_UNKNOWN:
      return 0;
  }
}