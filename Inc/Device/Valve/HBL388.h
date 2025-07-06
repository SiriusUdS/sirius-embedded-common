#pragma once

#include "Valve.h"

#define HBL388_OPERATING_FREQUENCY_HZ 333

#define HBL388_PSC 4
#define HBL388_ARR 57656

#define HBL388_PWM_DUTY_CYCLE_MIN_CCR 0
#define HBL388_PWM_DUTY_CYCLE_MAX_CCR HBL388_ARR

// Obtained from calibration
#define HBL388_PWM_OPENED_DUTY_CYCLE_PCT 26
#define HBL388_PWM_CLOSED_DUTY_CYCLE_PCT 54

#define HBL388_PWM_REVERSED_OPENED_DUTY_CYCLE_PCT HBL388_PWM_CLOSED_DUTY_CYCLE_PCT
#define HBL388_PWM_REVERSED_CLOSED_DUTY_CYCLE_PCT HBL388_PWM_OPENED_DUTY_CYCLE_PCT

#define HBL388_OPENED_DUTY_CYCLE_CCR (HBL388_ARR * HBL388_PWM_OPENED_DUTY_CYCLE_PCT) / 100
#define HBL388_CLOSED_DUTY_CYCLE_CCR (HBL388_ARR * HBL388_PWM_CLOSED_DUTY_CYCLE_PCT) / 100

#define HBL388_ELAPSED_DELAY_MS 1
#define HBL388_STEP 10

void HBL388_init(Valve* instance);

void HBL388_setIdle(Valve* instance);

void HBL388_close(Valve* instance, uint32_t timestamp_ms);

void HBL388_open(Valve* instance, uint32_t timestamp_ms);

void HBL388_tick(Valve* instance, uint32_t timestamp_ms);

void HBL388_setOpenedPosition_pct(Valve* instance, uint32_t dutyCycle_pct);