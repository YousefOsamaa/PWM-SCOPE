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

#include "PWMScope_Interface.h"
#include "PWMScope_Private.h"


static f32 LOC_af32_SignalsParameters[3] = {0};
static f32 LOC_af32_OldSignalsParameters[3] = {0};

/**
 * @brief Initializes all the modules needed and prints the home screen
 * 
 * @return ErrorState_t 
 */
extern ErrorState_t PWMScope_enu_Initialization(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Initializations    
    NOKIA5110_enu_Initialization();    //Initializing LCD

    ICU_enu_Initialization(); //Initializing ICU
    
    //Drawing Scope Screen
    enu_GenerateScopeScreen();

    //Displaying Frequency in HZ
    NOKIA5110_enu_DrawNumber(LOC_af32_SignalsParameters[0], 0, 30, NOKIA5110_BLACK_COLOUR);
            
    //Displaying Duty Ratio in %
    NOKIA5110_enu_DrawNumber(LOC_af32_SignalsParameters[1], 9, 30, NOKIA5110_BLACK_COLOUR);

    //Setting GIE
    SREG_vid_EnableBitI();

    return Local_u8_ErrorFlag;
}

/**
 * @brief A superloop that constantly displays the imposed waveform on the ICP1 pin
 * 
 */

extern ErrorState_t PWMScope_enu_RunScope(void)
{
    u8 Local_u8_NewWave = False;

    while(1)
    {
        //Saving Old Values
        LOC_af32_OldSignalsParameters[0] = LOC_af32_SignalsParameters[0];
        LOC_af32_OldSignalsParameters[1] = LOC_af32_SignalsParameters[1];
        LOC_af32_OldSignalsParameters[2] = LOC_af32_SignalsParameters[2];

        ICU_enu_StartCapture();//Starting a capture
        
        ICU_enu_CalculateParameters(LOC_af32_SignalsParameters);//Calculating Parameters
        
        Local_u8_NewWave = (LOC_af32_OldSignalsParameters[0] != LOC_af32_SignalsParameters[0]) || (LOC_af32_OldSignalsParameters[1] != LOC_af32_SignalsParameters[1]) || (LOC_af32_OldSignalsParameters[2] != LOC_af32_SignalsParameters[2]);

        if(Local_u8_NewWave)
        {
            //Displaying Frequency in HZ
            NOKIA5110_enu_DrawNumber(LOC_af32_SignalsParameters[0], 0, 30, NOKIA5110_BLACK_COLOUR);
            
            //Displaying Duty Ratio in %
            NOKIA5110_enu_DrawNumber(LOC_af32_SignalsParameters[1], 9, 30, NOKIA5110_BLACK_COLOUR);
            
            //Graphics
        }



    }
}

//Local Functions
/**
 * @brief Prints the homescreen using the defined configurations in the private header file
 * 
 * @return ErrorState_t 
 */
static ErrorState_t enu_GenerateScopeScreen(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Drawing Boarders
    //NOKIA5110_enu_DrawHorizontalLine(PWMSCOPE_BORDER_VERTICAL_SHIFT, PWMSCOPE_BORDER_HORIZOTAL_SHIFT, PWMSCOPE_BORDER_LENGTH, PWMSCOPE_BORDER_THICKNESS, PWMSCOPE_BORDER_COLOUR);

    //Drawing Static Texts
	NOKIA5110_enu_DrawString("Freq       kHz", 0, NOKIA5110_X_COORDINATE_MIN, NOKIA5110_BLACK_COLOUR);
	NOKIA5110_enu_DrawString("Duty        %", 9, NOKIA5110_X_COORDINATE_MIN, NOKIA5110_BLACK_COLOUR);

    //Drawing axis
    NOKIA5110_enu_DrawHorizontalLine(PWMSCOPE_X_AXIS_VERTICAL_SHIFT, PWMSCOPE_X_AXIS_HORIZOTAL_SHIFT, PWMSCOPE_X_AXIS_LENGTH, PWMSCOPE_X_AXIS_THICKNESS, PWMSCOPE_X_AXIS_COLOUR);
    NOKIA5110_enu_DrawVerticalLine(PWMSCOPE_Y_AXIS_VERTICAL_SHIFT, PWMSCOPE_Y_AXIS_HORIZOTAL_SHIFT, PWMSCOPE_Y_AXIS_HEIGHT, PWMSCOPE_Y_AXIS_THICKNESS, PWMSCOPE_Y_AXIS_COLOUR);

    //Drawing Arrows 
    NOKIA5110_enu_DrawCharacter(0x5E, PWMSCOPE_Y_AXIS_VERTICAL_SHIFT, PWMSCOPE_Y_AXIS_HORIZOTAL_SHIFT -2, PWMSCOPE_Y_AXIS_COLOUR, NOKIA5110_ENABLE_OVERLAP);
    NOKIA5110_enu_DrawCharacter(0x3E, PWMSCOPE_X_AXIS_VERTICAL_SHIFT - 3, PWMSCOPE_X_AXIS_HORIZOTAL_SHIFT + 79, PWMSCOPE_X_AXIS_COLOUR, NOKIA5110_ENABLE_OVERLAP);

    //Drawing Scale
    
    return Local_u8_ErrorFlag;
}