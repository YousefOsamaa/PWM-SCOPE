/**
 * @file General.h
 * @author your name (Youssef Osama)
 * @brief Contains general macros and functios
 * @version 0.1
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "General.h"

/**
 * @brief Returns the absolute of any number up to 32 bits
 * 
 * @param Copy_pf32_Number  Any number
 * @return ErrorState_t 
 */
extern ErrorState_t General_enu_AbsoluteIntegers(s32* Copy_ps32_IntegerNumber)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_ps32_IntegerNumber)
    {
        *Copy_ps32_IntegerNumber = (*Copy_ps32_IntegerNumber < 0)? -1*(*Copy_ps32_IntegerNumber) : (*Copy_ps32_IntegerNumber);

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFlag;
}