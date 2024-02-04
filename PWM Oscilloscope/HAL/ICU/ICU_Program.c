//General local files
#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"

//Other needed peripherals
#include "../../MCAL/EXTI/EXTI_Interface.h"
#include "../../MCAL/Timer/Timer_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../LCD/LCD_Interface.h"
#include "../../MCAL/Timer1/Timer1_Interface.h"

//ICU Module local files
#include "ICU_Config.h"
#include "ICU_Private.h"

static u8 LOC_u8_State = ICU_IDLE; //State by default IDLE 
static u32 LOC_u32_PeriodCounts; //Variable to store the  period counts in it
static u32 LOC_u32_TonCounts; //Variable to store Ton counts in it
static u32 LOC_au32_NumberOfOverflowsArray[3];  //To sotre the number of overflows performed by ICU_TIMER_USED (Total, Falling Edge, Second Rising Edge)
static u16 LOC_u16_Timer_PS;


extern ErrorState_t ICU_enu_Initialization()
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Initialize Timer peripheral: Timer1, Normal, PS 1024, and  Interrupt Mode for overflow and input capture
    Timer1_enu_Initialization();
    Timer1_enu_DisableInterrupt(TIMER1_CAPTURE_EVENT_ISR);
    Timer1_enu_SetCallBackFunction(TIMER1_CAPTURE_EVENT_ISR, vid_CapturingFunction, NULL);
    Timer1_enu_SetCallBackFunction(TIMER1_OVERFLOW_ISR, vid_IncrementOverFlowCounter, NULL);
    Timer1_enu_DisableInterrupt(TIMER1_OVERFLOW_ISR);


    //Initialize ICU module
    LOC_u8_State = ICU_IDLE; //State machine must start as IDLE until activation


    //Initialize EXTI peripheral: EXTI0, INT Mode, Rising Edge
    // EXTI_enu_Initialization();
    // EXTI_enu_INTMode(ICU_EXTI_USED, EXTI_POLLING_MODE); //Preventing EXTI from causing an interrupt until ICU activation
    // EXTI_enu_SetCallBack(ICU_EXTI_USED, vid_CapturingFunction, NULL); //Setting CapturingFunction as the EXTI ISR
    // Timer_enu_Initialization();
    // Timer_enu_DisableInterruptMode(ICU_TIMER_USED, TIMER_NORMAL); //Disabling Timer Interrupt
    // Timer_enu_SetCallBack(ICU_TIMER_USED, TIMER_NORMAL, vid_IncrementOverFlowCounter, NULL);//Setting Call Back Function

    return Local_u8_ErrorFlag;

}

extern ErrorState_t ICU_enu_StartCapture()
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    
    if(LOC_u8_State == ICU_IDLE)
    {
        
        LOC_u8_State = ICU_FIRST_RISING_EDGE; //State machine will begin from the 'FIRS_RISING_EGDE' State
        
        Timer1_enu_GetPS(&LOC_u16_Timer_PS);
        
        Timer1_enu_SetInputCaptureEdge(TIMER1_ICU_RISING_EDGE);

        Timer1_enu_ClearFlag(TIMER1_CAPTURE_EVENT_ISR); //Clearing Flag in case of pending interrupts
        
        Timer1_enu_ClearFlag(TIMER1_OVERFLOW_ISR); //Clearing Flag in case of pending interrupts

        Timer1_enu_EnableInterrupt(TIMER1_CAPTURE_EVENT_ISR);
    
        Timer1_enu_EnableInterrupt(TIMER1_OVERFLOW_ISR);
    }

    return Local_u8_ErrorFlag;
}

extern ErrorState_t ICU_enu_CalculateParameters(f32* Copy_pf32_SignalParametersArray)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    f32 Local_f32_TimerFrequency = 16000000.0/LOC_u16_Timer_PS; 
    
    if(LOC_u8_State == ICU_IDLE)
    {

        LOC_u32_PeriodCounts += 65536ULL*LOC_au32_NumberOfOverflowsArray[2]; //Total Number of Period Counts

        LOC_u32_TonCounts += 65536ULL*LOC_au32_NumberOfOverflowsArray[1]; //Total Number of Duty Counts

        //Calculating Frequency in Hz
        if(LOC_u32_PeriodCounts != 0)
        {
            Copy_pf32_SignalParametersArray[0] = (Local_f32_TimerFrequency/LOC_u32_PeriodCounts);
        }
        else
        {
            Copy_pf32_SignalParametersArray[0] = 0; //dc
        }

        if(LOC_u32_PeriodCounts != 0)
        {
            //Calculating Duty Ratio in %
            Copy_pf32_SignalParametersArray[1] = ((f32)LOC_u32_TonCounts*100UL)/(LOC_u32_PeriodCounts);
        }   
        else
        {
            Copy_pf32_SignalParametersArray[1] = 100; 
        }
    
    }

    return Local_u8_ErrorFlag;
}

extern ErrorState_t ICU_enu_GetState(u8* Copy_pu8_SystemState)
{
    u8 Local_u8_ErrorFlag;

    if(Copy_pu8_SystemState)
    {
        *Copy_pu8_SystemState = LOC_u8_State;
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFlag;
}

u16 TestVariable;
void vid_CapturingFunction(void* Copy_pvid_FunctionParameters)
{

    switch (LOC_u8_State)
    {
        
        
        case ICU_FIRST_RISING_EDGE:
        {
            
            Timer1_enu_SetTCNT1(0);

            LOC_au32_NumberOfOverflowsArray[0] = 0; //Resetting Overflow Counter

            Timer1_enu_SetInputCaptureEdge(TIMER1_ICU_FALLING_EDGE);            
            
            LOC_u8_State = ICU_FALLING_EDGE;  //Setting state machine to Falling edge
            

            break;
        }

        case ICU_FALLING_EDGE:
        {
            
            Timer1_enu_GetICR1(&LOC_u32_TonCounts);

            LOC_au32_NumberOfOverflowsArray[1] = LOC_au32_NumberOfOverflowsArray[0];
            
            Timer1_enu_SetInputCaptureEdge(TIMER1_ICU_RISING_EDGE);
            
            LOC_u8_State = ICU_SECOND_RISING_EDGE; //Setting state machine to Falling edge
            
            


            break;
        }
        
        case ICU_SECOND_RISING_EDGE:
        {
            Timer1_enu_GetICR1(&LOC_u32_PeriodCounts);
            
            LOC_au32_NumberOfOverflowsArray[2] = LOC_au32_NumberOfOverflowsArray[0];

            #if ICU_MODE == ICU_SNGLE_CAPTURE_MODE
            Timer1_enu_DisableInterrupt(TIMER1_CAPTURE_EVENT_ISR);
            Timer1_enu_DisableInterrupt(TIMER1_OVERFLOW_ISR);
            LOC_u8_State = ICU_IDLE;
            #else
            #endif

            // LCD_enu_WriteIntegerNum(LOC_u32_TonCounts, LCD_ROW_1, LCD_COLUMN_1, LCD_PAGE_1);
            
            // LCD_enu_WriteIntegerNum(LOC_au32_NumberOfOverflowsArray[1], LCD_ROW_1, LCD_COLUMN_8, LCD_PAGE_1);
            
            // LCD_enu_WriteIntegerNum(LOC_u32_PeriodCounts, LCD_ROW_2, LCD_COLUMN_1, LCD_PAGE_1);
            // LCD_enu_WriteIntegerNum(LOC_au32_NumberOfOverflowsArray[2], LCD_ROW_2, LCD_COLUMN_8, LCD_PAGE_1);
            
            break;

        }
    
        case ICU_IDLE:
        {
            //Redundant case    
            break;
        }

        default:
        {
            break;
        }

    }
    
}

void vid_IncrementOverFlowCounter()
{

    LOC_au32_NumberOfOverflowsArray[0]++;
    
}
