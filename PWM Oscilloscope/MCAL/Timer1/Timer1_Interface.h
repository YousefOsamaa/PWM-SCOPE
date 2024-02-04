#ifndef TIMER1_INTERFACE
#define TIMER1_INTERFACE

#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"

//Clock Selection Options
#define TIMER1_V_GND             0
#define TIMER1_PS_1              1
#define TIMER1_PS_8              2   
#define TIMER1_PS_64             3
#define TIMER1_PS_256            4
#define TIMER1_PS_1024           5
#define TIMER1_FALLING_EGDE      6   
#define TIMER1_RISING_EGDE       7  

//Timer Modes
#define TIMER1_NORMAL           0
#define TIMER1_CTC              1

//Input Capture Edge Mode 
#define TIMER1_ICU_RISING_EDGE                       1
#define TIMER1_ICU_FALLING_EDGE                      0

//ISR Pointers Location
#define TIMER1_CAPTURE_EVENT_ISR       0
#define TIMER1_CTC_A_ISR               1
#define TIMER1_CTC_B_ISR               2
#define TIMER1_OVERFLOW_ISR            3


extern ErrorState_t Timer1_enu_Initialization(void);

extern ErrorState_t Timer1_enu_GetICR1(u16* Copy_u16_ContentOfICR1);

extern ErrorState_t Timer1_enu_SetTCNT1(u16 Copy_u16_WrittenValue);

extern ErrorState_t Timer1_enu_GetTCNT1(u16* Copy_u16_ContentOfTCNT1);

extern ErrorState_t Timer1_enu_SetCallBackFunction(u8 Copy_u8_InterruptType, void (*Copy_pfun_AppFunction)(void*), void* Copy_pvid_Prameters);

extern ErrorState_t Timer1_enu_DisableInterrupt(u8 Copy_u8_InterruptType);

extern ErrorState_t Timer1_enu_EnableInterrupt(u8 Copy_u8_InterruptType);

extern ErrorState_t Timer1_enu_GetPS(u16* Copy_u16_PsUsed);

extern ErrorState_t Timer1_enu_SetInputCaptureEdge(u8 Copy_u8_EdgeType);

extern ErrorState_t Timer1_enu_ClearFlag(u8 Copy_u8_InterruptType);

#endif