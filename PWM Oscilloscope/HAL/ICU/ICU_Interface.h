#ifndef ICU_INTERFACE
#define ICU_INTERFACE


#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"


typedef enum
{
    ICU_IDLE,
    ICU_FIRST_RISING_EDGE,
    ICU_SECOND_RISING_EDGE,
    ICU_FALLING_EDGE,

}ICU_States;

extern ErrorState_t ICU_enu_Initialization();

extern ErrorState_t ICU_enu_StartCapture();

extern ErrorState_t ICU_enu_CalculateParameters(u32* Copy_pu32_SignalParametersArray);

extern ErrorState_t ICU_enu_GetState(u8* Copy_pu8_SystemState);


#endif