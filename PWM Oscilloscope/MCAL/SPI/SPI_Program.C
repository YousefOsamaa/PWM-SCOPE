#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"
#include "../../HAL/LCD/LCD_Interface.h"


#include "SPI_Config.h"
#include "SPI_Private.h"



u8 LOC_u8_SPIState = SPI_FREE; //SPI Communication Status

void (*LOC_pfun_ISR)(void*) = NULL;

void* LOC_pvid_ParametersOfISR = NULL;


extern ErrorState_t SPI_enu_Initialization (void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
     
    //MCU SPI Mode 
    #if SPI_MCU_MODE == SPI_MASTER_MODE

        SPCR |= (1 << SPCR_MSTR);


        //Clock Selection only affects Master
        SPCR &= ~(3 << SPCR_SPR0); //Masking SPI Rate bits SPR1:0
        #if SPI_PS == SPI_PS_4
        
            //Bits already contain 00 
        
        #elif SPI_PS == SPI_PS_16
        
            //Bits contain  0 1
            SPCR |= (1 << SPCR_SPR0);

        #elif SPI_PS == SPI_PS_64
        
            //Bits contain  1 0
            SPCR |= (1 << SPCR_SPR1);
        
        #elif SPI_PS == SPI_PS_128
            //Bits contain  1 1
            SPCR |= (3 << SPCR_SPR0);
        
        #else
            
            #error SPI_PS is invalid

        #endif

        //Configuring Double Speed Mode
        #if SPI_DOUBLE_SPEED_MODE == SPI_ACTIVATE_DOUPLE_SPEED_MODE
        
            SPSR |= (1 << SPSR_SPI2X);

        #elif SPI_DOUBLE_SPEED_MODE == SPI_DEACTIVATE_DOUPLE_SPEED_MODE
        
            SPSR &= ~(1 << SPSR_SPI2X);

        #else
        
            #error SPI_DOUBLE_SPEED_MODE is invalid
        
        #endif

    #elif SPI_MCU_MODE == SPI_SLAVE_MODE
    
        SPCR &= ~(1 << SPCR_MSTR);
    
    #else
        
        #error SPI_MCU_MODE is invalid
    
    #endif 

    //Interrupt Mode
    #if SPI_INTERRUPT_MODE == SPI_ACTIVATE_INTERRUPT_MODE

        SPCR |= (1 << SPCR_SPIE);

    #elif SPI_INTERRUPT_MODE == SPI_ACTIVATE_POLLING_MODE
    
        SPCR &= ~(1 << SPCR_SPIE);

    #else

        #error SPI_INTERRUPT_MODE is invalid

    #endif

    //Clock Polarity Selection
    #if SPI_CPOL_MODE == SPI_CPOL_LOW_IDLE

        SPCR &= ~(1 << SPCR_CPOL);

    #elif SPI_CPOL_MODE == SPI_CPOL_HIGH_IDLE
        
        SPCR |= (1 << SPCR_CPOL);
    
    #else
    
        #error SPI_CPOL_MODE is invalid

    #endif

    //Clock Phase Selection
    #if SPI_CPHA_MODE == SPI_CPHA_SAMPLE_LEADING

        SPCR &= ~(1 << SPCR_CPHA);

    #elif SPI_CPOL_MODE == SPI_CPHA_SAMPLE_LAGGING
        
        SPCR |= (1 << SPCR_CPHA);
    
    #else
    
        #error SPI_CPHA_MODE is invalid

    #endif

    //Data Order Selection 
    #if SPI_DORD_MODE == SPI_DORD_MSB_FIRST

        SPCR &= ~(1 << SPCR_DORD);

    #elif SPI_DORD_MODE == SPI_DORD_LSB_FIRST

        SPCR |= (1 << SPCR_DORD);
    
    #else
    
        #error SPI_DORD_MODE is invalid

    #endif

    //Enabling SPI
    SPCR |= (1<< SPCR_SPE);

    return Local_u8_ErrorFlag;
}

extern ErrorState_t SPI_enu_StartTranReceive (u8* Copy_u8_TranReceivedData)
{
	u8 Local_u8_ErrorFlag = ES_NOK;
    
    if(LOC_u8_SPIState == SPI_BUSY)
    {
        Local_u8_ErrorFlag = ES_WAIT;
    }
    else
    {

    SPDR = *Copy_u8_TranReceivedData; //Placing Data in SPDR

    while (!(SPSR >> SPSR_SPIF) & 1); //Trapping CPU until the data is exchanged after 8 clk pulses

    *Copy_u8_TranReceivedData = SPDR; //Receiving Data from Slave

    }
    return Local_u8_ErrorFlag;

}

extern ErrorState_t SPI_enu_MasterSend(u8 Copy_u8_Data)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(LOC_u8_SPIState == SPI_BUSY) //Checking if the SPI Moudle is available
    {

        Local_u8_ErrorFlag = ES_WAIT; //Signalling that the SPI MOdule is busy

    }
    else if(LOC_u8_SPIState == SPI_FREE)
    {
        //Sending Data
        SPDR = Copy_u8_Data;

        //Incase of polling mode SPI clear its state after trapping the CPU until SPIF is raised
        #if SPI_INTERRUPT_MODE == SPI_ACTIVATE_POLLING_MODE
            LOC_u8_SPIState = SPI_BUSY;

            while(!((SPSR >> SPSR_SPIF) & 1))

            Copy_u8_Data = SPDR; //Redundant line to clear SPIF 

            LOC_u8_SPIState = SPI_FREE; //Returning SPI State as Free
        #elif SPI_INTERRUPT_MODE == SPI_ACTIVATE_INTERRUPT_MODE

            LOC_u8_SPIState = SPI_BUSY; //Setting SPI State as busy to avoid data collision

        #endif

        Local_u8_ErrorFlag = ES_OK;
        
    }

    return Local_u8_ErrorFlag;

}

extern ErrorState_t SPI_enu_SlaveReceive(u8* Copy_pu8_Data)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    #if SPI_INTERRUPT_MODE == SPI_ACTIVATE_POLLING_MODE
        while(!((SPSR >> SPSR_SPIF) & 1)); //Trappin MCU until SPIF is raised
        
        *Copy_pu8_Data = SPDR; //Saving Data

        LOC_u8_SPIState = SPI_FREE; //Setting state as FREE (Redundant)
    #elif SPI_INTERRUPT_MODE == SPI_ACTIVATE_INTERRUPT_MODE
        if(LOC_u8_SPIState == SPI_FREE)
        {
            //Receiving Data
            *Copy_pu8_Data = SPDR;

        }
        else
        {
            Local_u8_ErrorFlag = ES_WAIT;
        }
    #endif

    return Local_u8_ErrorFlag;
}

extern ErrorState_t SPI_enu_SetCommStateBusy(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    LOC_u8_SPIState = SPI_BUSY;

    return Local_u8_ErrorFlag;
}

extern ErrorState_t SPI_enu_GetCommState(u8* Copy_pu8_State)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_pu8_State)
    {
        *Copy_pu8_State = LOC_u8_SPIState;

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFlag; 
}

extern ErrorState_t SPI_enu_SetCallBack(void (*Copy_pfun_AppFunction)(void*), void* Copy_pvid_Parameters)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_pfun_AppFunction)
    {
        LOC_pfun_ISR = Copy_pfun_AppFunction;

        LOC_pvid_ParametersOfISR =Copy_pvid_Parameters;

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFlag;

}

extern ErrorState_t SPI_enu_SetDataOrderMode(u8 Copy_u8_DataOrderMode)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    
    switch (Copy_u8_DataOrderMode)
    {
        case SPI_DORD_MSB_FIRST: 
        {
            SPCR &= ~(1<< SPCR_DORD); //Clearing bit
            
            Local_u8_ErrorFlag = ES_OK;
            break;
        }

        case SPI_DORD_LSB_FIRST: 
        {
            SPCR |= (1<< SPCR_DORD); //Setting bit
            
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

// ISR
void __vector_12 (void)__attribute__((signal));

void __vector_12 (void)
{
    #if SPI_ISR_STATUS == SPI_INTERNAL_ISR        
    
        #if SPI_MCU_MODE == SPI_MASTER_MODE
    
            if ((SPCR >> SPCR_MSTR) & 1) // Making sure the SPIF was rasied due to an SPI operation ending
            {
                LOC_u8_SPIState = SPI_FREE;
                //LCD_enu_SendString("3");
            }
            else
            {
                // SPCR |= (1 << SPCR_MSTR); //Reassinging the MCU as masterr
            }
    
        #elif SPI_MCU_MODE == SPI_SLAVE_MODE
            LOC_u8_SPIState = SPI_FREE;
    
        #else
    
            #error SPI_MCU_MODE is invalid
    
        #endif
    
    #elif SPI_EXTERNAL_ISR == SPI_EXTERNAL_ISR

        LOC_pfun_ISR(LOC_pvid_ParametersOfISR); //Calling App function

    #else
    
        #error SPI_EXTERNAL_ISR is invald
    
    #endif
}


