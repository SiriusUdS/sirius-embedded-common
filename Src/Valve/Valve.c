#include "../../Inc/Devices/Valve/Valve.h"

static volatile Valve valve;

static int closeState();

static int openState();

static void setCCR(int16_t cycle);


TIM_HandleTypeDef htim;

void VALVE_init(TIM_HandleTypeDef ht, uint16_t prescale){
    htim = ht;
    HAL_TIM_Base_Stop_IT(&htim);
    __HAL_TIM_SET_PRESCALER(&htim, prescale);
    if(HAL_TIM_Base_Start_IT(&htim) != HAL_OK){
        return;
    }
    setCCR(PWM_DUTY_CYCLE_MIN);
    
    HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1);
    valve.state = VALVE_CLOSED;
}

void VALVE_SetState(ValveState _state){
    if(_state == valve.state) return;
    int operation = 0;

    switch(_state){
        case VALVE_CLOSED:
            operation = closeState();
            break;
        case VALVE_OPENED:
            operation = openState();
            break;
        default:
            break;
    }

    if(operation == 0){
        valve.state = VALVE_PENDING;
        return;
    }

    valve.state = _state;
}

uint16_t VALVE_GetActualCycle(){
    return valve.actualCycle;
}

ValveState VALVE_GetState(){
    return valve.state;
}

void setCCR(int16_t cycle){
    if(cycle < PWM_DUTY_CYCLE_MIN){
        cycle = PWM_DUTY_CYCLE_MIN;
    }

    if(cycle > PWM_DUTY_CYCLE_MAX){
        cycle = PWM_DUTY_CYCLE_MAX;
    }

    TIM1->CCR1 = cycle;
    valve.actualCycle = cycle;
    valve.CycleLastTime = HAL_GetTick();
}


int closeState(){
    if(valve.actualCycle <= PWM_DUTY_CYCLE_MIN) return 1;

    if(HAL_GetTick() - valve.CycleLastTime >= ELAPSED_DELAY_MS){
        setCCR(valve.actualCycle - ELAPSED_STEP);
    }

    return 0;
}

int openState(){
    if(valve.actualCycle == PWM_DUTY_CYCLE_MAX) return 1;

    if(HAL_GetTick() - valve.CycleLastTime >= ELAPSED_DELAY_MS){
        setCCR(valve.actualCycle + ELAPSED_STEP);
    }

    return 0;
}



