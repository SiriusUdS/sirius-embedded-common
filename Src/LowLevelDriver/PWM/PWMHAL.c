#include "../../../Inc/LowLevelDriver/PWM/PWMHAL.h"

#include "stm32f4xx_hal.h"

void PWMHAL_init(PWM* instance) {
  instance->status.value = 0;
  instance->errorStatus.value = 0;
  TIM_HandleTypeDef* halHandle = (TIM_HandleTypeDef*)instance->externalHandle;

  HAL_TIM_Base_Stop_IT(halHandle);
  __HAL_TIM_SET_PRESCALER(halHandle, instance->prescaler);
  if(HAL_TIM_Base_Start_IT(halHandle) != HAL_OK) {
    return;
  }

  HAL_TIM_PWM_Start(halHandle, instance->channel);

  instance->setDutyCycle(instance, instance->minDutyCycle_CCR);
}

// À FAIRE : FAIRE UNE TABLE DE CCR POUR COUVRIR LES DUTY CYCLE (SPEED)
void PWMHAL_setDutyCycle(PWM* instance, uint8_t dutyCycle_pct) {
  uint16_t dutyCycleCCR = 16000; // Convertir pct en CCR
  if (dutyCycleCCR < instance->minDutyCycle_CCR) {
    dutyCycleCCR = instance->minDutyCycle_CCR;
  }

  if(dutyCycleCCR > instance->maxDutyCycle_CCR){
    dutyCycleCCR = instance->maxDutyCycle_CCR;
  }

  TIM1->CCR1 = dutyCycleCCR;
  instance->currentDutyCycle_CCR = dutyCycleCCR;
  instance->lastDutyCycleChangeTime_ms = HAL_GetTick();
}
