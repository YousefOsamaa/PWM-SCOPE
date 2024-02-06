/**
 * @file PWM_Oscilloscope.c
 * @author Youssef Osama 
 * @brief 
 * @version 0.1
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PWM_OSCILLOSCOPE_H_
#define PWM_OSCILLOSCOPE_H_

#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"

#include "../../HAL/ICU/ICU_Interface.h"
#include "../../HAL/Nokia5110/Nokia5110_Interface.h"

#include "../../MCAL/SREG/SREG_Interface.h"

extern ErrorState_t PWMScope_enu_Initialization(void);

extern ErrorState_t PWMScope_enu_RunScope(void);

#endif /* PWM_OSCILLOSCOPE_H_ */