#ifndef ICU_INTERFACE
#define ICU_INTERFACE


#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"


extern ErrorState_t ICU_enu_Initialization();

extern ErrorState_t ICU_enu_StartCapture();

extern ErrorState_t ICU_enu_CalculateParameters(f32* Copy_pf32_SignalParametersArray);

extern ErrorState_t ICU_enu_GetState(u8* Copy_pu8_SystemState);


#endif