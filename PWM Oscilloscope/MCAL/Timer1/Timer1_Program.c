#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"


#include "Timer1_Config.h"
#include "Timer1_Private.h"


static void (*LOC_apfun_IntServiceRoutinesFunctions[TIMER1_ISR_COUNT])(void* ) = {NULL};
static void (*LOC_apvid_IntServiceRoutinesParameters[TIMER1_ISR_COUNT])(void* ) = {NULL};


extern ErrorState_t Timer1_enu_Initialization(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    

    //Waveform Generation Mode and Interrupt Mode Selection
    #if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL

        //Clearing WGM11:0
        TCCR1A &= 0xFC;
        //Clearing WGM13:2
        TCCR1B &= 0xE7;

        //Configuring Overflow interrupt
        #if TIMER1_INTERRUPT_MODE  == TIMER1_ACTIVATE_INT_MODE

            //Setting TOIE1 bit 
            TIMSK |= ( 1 << TIMSK_TOIE1);

        #elif TIMER1_INTERRUPT_MODE  == TIMER1_ACTIVATE_POLLING_MODE

            //Clearing TOIE1 bit 
            TIMSK &= ~( 1 << TIMSK_TOIE1);

        #else
            
            #error TIMER1_INTERRUPT_MODE is invalid
        
        #endif



    #else
        
        #error  TIMER1_WAVEFORM_GENERATION_MODE is invalid 

    #endif


    //Input Capture Mode Edge Selection
    #if TIMER1_INPUT_CAPTURE_MODE == TIMER1_ICU_FALLING_EDGE
        
        //Clearing  ICES1 bit
        TCCR1B &= ~(1 << TCCR1B_ICES1);

    #elif   TIMER1_INPUT_CAPTURE_MODE == TIMER1_ICU_RISING_EDGE
        
        //Setting  ICES1 bit
        TCCR1B |= (1 << TCCR1B_ICES1);

    #else
        


    #endif


    //Input Capture Mode Interrupt 
    #if TIMER1_INPUT_CAPTURE_INTERRUPT_MODE == TIMER1_DEACTIVATE_ICU_INTERRUPT 

        //Settting TICIE1 bit    
        TIMSK &= ~(1 << TIMSK_TICIE1);

    #elif TIMER1_INPUT_CAPTURE_INTERRUPT_MODE ==  TIMER1_ACTIVATE_ICU_INTERRUPT 

        //Settting TICIE1 bit    
        TIMSK |= (1 << TIMSK_TICIE1);
    
    #else

        #error TIMER1_INPUT_CAPTURE_INTERRUPT_MODE is invalid

    #endif

    //Noise Canceler Configuration
    #if TIMER1_NOISE_CANCELER_MODE == TIMER1_ACTIVATE_NC
        
        TCCR1B |= (1 << TCCR1B_ICNC1);

    #elif TIMER1_NOISE_CANCELER_MODE == TIMER1_DEACTIVATE_NC

        TCCR1B &= ~(1 << TCCR1B_ICNC1);

    #else
        #error TIMER1_NOISE_CANCELER_MODE is invalid
    #endif


    //Clock Selection
    TCCR1B &= 0xF8; //Clearing CS12:0 bits
    #if TIMER1_CLOCK_SELECTION == TIMER1_V_GND
        
        //Bits already cleared

    #elif TIMER1_CLOCK_SELECTION ==  TIMER1_PS_1

        //Bits contain 0 0 1
        TCCR1B |= (1 << TCCR1B_CS10);

    #elif TIMER1_CLOCK_SELECTION ==  TIMER1_PS_8

        //Bits contain 0 1 0
        TCCR1B |= (1 << TCCR1B_CS11);
    
    #elif TIMER1_CLOCK_SELECTION ==  TIMER1_PS_64

        //Bits contain 0 1 1
        TCCR1B |= (1 << TCCR1B_CS10);
        TCCR1B |= (1 << TCCR1B_CS11);
    
    #elif TIMER1_CLOCK_SELECTION ==  TIMER1_PS_256
    
        //Bits contain 1 0 0
        TCCR1B |= (1 << TCCR1B_CS12);

    #elif TIMER1_CLOCK_SELECTION ==  TIMER1_PS_1024
    
        //Bits contain 1 0 1
        TCCR1B |= (1 << TCCR1B_CS10);
        TCCR1B |= (1 << TCCR1B_CS12);

    #elif TIMER1_CLOCK_SELECTION ==  TIMER1_PS_FALLING_EGDE

        //Bits contain 1 1 0
        TCCR1B |= (1 << TCCR1B_CS11);
        TCCR1B |= (1 << TCCR1B_CS12);
    
    #elif TIMER1_CLOCK_SELECTION ==  TIMER1_PS_RISING_EGDE

        //Bits contain 1 1 1
        TCCR1B |= (7 << TCCR1B_CS10);

    #else
        
        #error TIMER1_CLOCK_SELECTION is in valid

    #endif

    return Local_u8_ErrorFlag;
}

extern ErrorState_t Timer1_enu_GetICR1(u16* Copy_u16_ContentOfICR1)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_u16_ContentOfICR1)
    {
        //Reading Low Byte
        *Copy_u16_ContentOfICR1= ICR1L;

        //Reading High Byte
        *Copy_u16_ContentOfICR1 |= (u16)ICR1H << 8;
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFlag; 
}

extern ErrorState_t Timer1_enu_SetTCNT1(u16 Copy_u16_WrittenValue)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    
    //Wriiting High Byte
    TCNT1H = Copy_u16_WrittenValue >> 8;

    //Writing Low Byte
    TCNT1L = Copy_u16_WrittenValue;
    
    return Local_u8_ErrorFlag;
}

extern ErrorState_t Timer1_enu_GetTCNT1(u16* Copy_u16_ContentOfTCNT1)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_u16_ContentOfTCNT1)
    {
        //Reading Low Byte
        *Copy_u16_ContentOfTCNT1 = TCNT1L;

        //Reading High Byte
        *Copy_u16_ContentOfTCNT1 |= (u16)TCNT1H << 8;
        
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFlag;
}

extern ErrorState_t Timer1_enu_SetCallBackFunction(u8 Copy_u8_InterruptType, void (*Copy_pfun_AppFunction)(void*), void* Copy_pvid_Prameters)
{
    u8 Local_u8_ErrorFLag = Local_u8_ErrorFLag;

    if(Copy_pfun_AppFunction)
    {
        LOC_apfun_IntServiceRoutinesFunctions[Copy_u8_InterruptType] = Copy_pfun_AppFunction;

        LOC_apvid_IntServiceRoutinesParameters[Copy_u8_InterruptType] = Copy_pvid_Prameters;
    }
    else
    {
        Local_u8_ErrorFLag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFLag;
}

extern ErrorState_t Timer1_enu_DisableInterrupt(u8 Copy_u8_InterruptType)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    
    switch (Copy_u8_InterruptType)
    {
        case TIMER1_CAPTURE_EVENT_ISR:
        {
            TIMSK &= ~(1<< TIMSK_TICIE1);

            break;
        } 
        case TIMER1_CTC_A_ISR:
        {
            TIMSK &= ~(1<< TIMSK_OCIE1A);

            break;
        } 
        case TIMER1_CTC_B_ISR:
        {
            TIMSK &= ~(1<< TIMSK_OCIE1A);

            break;
        } 

        case TIMER1_OVERFLOW_ISR:
        {
            TIMSK &= ~(1<< TIMSK_TOIE1);
            
            break;
        } 
    
        default:
        {
            Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
            break;
        }
    }
    return Local_u8_ErrorFlag;
}

extern ErrorState_t Timer1_enu_EnableInterrupt(u8 Copy_u8_InterruptType)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    switch (Copy_u8_InterruptType)
    {
        case TIMER1_CAPTURE_EVENT_ISR:
        {
            TIMSK |= (1<< TIMSK_TICIE1);

            Local_u8_ErrorFlag = ES_OK;

            break;
        } 
        case TIMER1_CTC_A_ISR:
        {
            TIMSK |= (1<< TIMSK_OCIE1A);

            break;
        } 
        case TIMER1_CTC_B_ISR:
        {
            TIMSK |= (1<< TIMSK_OCIE1A);

            Local_u8_ErrorFlag = ES_OK;
            break;
        } 

        case TIMER1_OVERFLOW_ISR:
        {
            TIMSK |= (1<< TIMSK_TOIE1);
            
            Local_u8_ErrorFlag = ES_OK;
            break;
        } 
    
        default:
        {
            Local_u8_ErrorFlag = ES_OUT_OF_RANGE;

            break;
        }
    }

    return Local_u8_ErrorFlag;
}

extern ErrorState_t Timer1_enu_GetPS(u16* Copy_pu16_PS)
{
    u8 Local_u8_ErrorFlag = ES_NOK;


    
        u8 Local_u8_CS_Bits = TCCR1B & 0x07; //Acquiring the least significant 3 bits CS2:0\

        switch (Local_u8_CS_Bits)
        {
            
            case 0:
            {
                *Copy_pu16_PS = 0;
                    
                    break;
            }

            case 1:
            {
                *Copy_pu16_PS = 1;

                break;
            }

            case 2:
            {
                *Copy_pu16_PS = 8;
                    
                break;
            }

            case 3:
            {
                *Copy_pu16_PS = 64;
                    
                break;
            }

            case 4:
            {
                *Copy_pu16_PS = 256;
                    
                break;
            }

            case 5:
            {
                *Copy_pu16_PS = 1024;
                    
                break;
            }

            default:
            {
                Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
                break;
            }
              
        }


    return Local_u8_ErrorFlag;
}

extern ErrorState_t Timer1_enu_SetInputCaptureEdge(u8 Copy_u8_EdgeType)
{
    u8 Local_u8_Error_Flag = ES_NOK;
    
    if(Copy_u8_EdgeType == TIMER1_ICU_FALLING_EDGE )
    {
        TCCR1B &= ~(1 << TCCR1B_ICES1);
    }
    else if( Copy_u8_EdgeType == TIMER1_ICU_RISING_EDGE)
    {
        TCCR1B |= (1 << TCCR1B_ICES1);
    }
    else
    {
        Local_u8_Error_Flag = ES_OUT_OF_RANGE;
    }
    return Local_u8_Error_Flag;
}

extern ErrorState_t Timer1_enu_ClearFlag(u8 Copy_u8_InterruptType)
{
    u8 Lcoal_u8_ErrorFlag = ES_NOK;

    switch (Copy_u8_InterruptType)
    {
        case TIMER1_CAPTURE_EVENT_ISR:
        {
            //Clearing Input Capture Flag
            TIFR |= (1 << TIFR_ICF1);

            Lcoal_u8_ErrorFlag = ES_OK;
            break;
        }

        case TIMER1_CTC_A_ISR:
        {
            //Clearing Output Compare Flag A
            TIFR |= (1 << TIFR_OCF1A);

            Lcoal_u8_ErrorFlag = ES_OK;
            break;
        }

        case TIMER1_CTC_B_ISR:
        {
            //Clearing Output Compare Flag B
            TIFR |= (1 << TIFR_OCF1B);

            Lcoal_u8_ErrorFlag = ES_OK;
            break;
        }

        case TIMER1_OVERFLOW_ISR:
        {
            //Clearing Overflow Flag 
            TIFR |= (1 << TIFR_TOV1);

            Lcoal_u8_ErrorFlag = ES_OK;
            break;
        }

        default:
        {
            Lcoal_u8_ErrorFlag = ES_OUT_OF_RANGE;
            break;
        }
    }
    return Lcoal_u8_ErrorFlag;
}



//ISR
void __vector_6 (void)__attribute__((signal));
void __vector_7 (void)__attribute__((signal));
void __vector_8 (void)__attribute__((signal));
void __vector_9 (void)__attribute__((signal));

void __vector_6 (void)
{
    if(LOC_apfun_IntServiceRoutinesFunctions[TIMER1_CAPTURE_EVENT_ISR])
    {
       LOC_apfun_IntServiceRoutinesFunctions[TIMER1_CAPTURE_EVENT_ISR](LOC_apvid_IntServiceRoutinesParameters[TIMER1_CAPTURE_EVENT_ISR]);
    }
}

void __vector_7 (void)
{
    if(LOC_apfun_IntServiceRoutinesFunctions[TIMER1_CTC_A_ISR])
    {
       LOC_apfun_IntServiceRoutinesFunctions[TIMER1_CTC_A_ISR](LOC_apvid_IntServiceRoutinesParameters[TIMER1_CTC_A_ISR]);
    }
}

void __vector_8 (void)
{
    if(LOC_apfun_IntServiceRoutinesFunctions[TIMER1_CTC_B_ISR])
    {
       LOC_apfun_IntServiceRoutinesFunctions[TIMER1_CTC_B_ISR](LOC_apvid_IntServiceRoutinesParameters[TIMER1_CTC_B_ISR]);
    }
}

void __vector_9 (void)
{
    if(LOC_apfun_IntServiceRoutinesFunctions[TIMER1_OVERFLOW_ISR])
    {
       LOC_apfun_IntServiceRoutinesFunctions[TIMER1_OVERFLOW_ISR](LOC_apvid_IntServiceRoutinesParameters[TIMER1_OVERFLOW_ISR]);
    }
}
