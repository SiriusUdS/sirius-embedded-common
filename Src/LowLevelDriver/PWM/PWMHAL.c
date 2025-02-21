#include "../../../Inc/LowLevelDriver/PWM/PWMHAL.h"

#include "stm32f4xx_hal.h"

void PWMHAL_init(PWM* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  TIM_HandleTypeDef* halHandle = (TIM_HandleTypeDef*)instance->externalHandle;

  HAL_TIM_Base_Stop_IT(halHandle);
  __HAL_TIM_SET_PRESCALER(halHandle, instance->prescaler);
  ((TIM_TypeDef *)(instance->timer))->ARR = instance->autoReload;
  if(HAL_TIM_Base_Start_IT(halHandle) != HAL_OK) {
    return;
  }

  HAL_TIM_PWM_Start(halHandle, instance->channel);

  instance->setDutyCycle(instance, instance->minDutyCycle_CCR);
}

void PWMHAL_setDutyCycle(PWM* instance, uint16_t dutyCycle_CCR) {
  if (dutyCycle_CCR < instance->minDutyCycle_CCR) {
    dutyCycle_CCR = instance->minDutyCycle_CCR;
  }

  if(dutyCycle_CCR > instance->maxDutyCycle_CCR){
    dutyCycle_CCR = instance->maxDutyCycle_CCR;
  }

  switch (instance->channel) {
    case TIM_CHANNEL_1:
      ((TIM_TypeDef *)(instance->timer))->CCR1 = dutyCycle_CCR;
      break;
    case TIM_CHANNEL_2:
      ((TIM_TypeDef *)(instance->timer))->CCR2 = dutyCycle_CCR;
      break;
    case TIM_CHANNEL_3:
    case TIM_CHANNEL_4:
    default:
      instance->errorStatus.bits.invalidTimerChannel = 1;
      break;
  }
  
  instance->currentDutyCycle_CCR = dutyCycle_CCR;
  instance->lastDutyCycleChangeTimestamp_ms = HAL_GetTick();
}
