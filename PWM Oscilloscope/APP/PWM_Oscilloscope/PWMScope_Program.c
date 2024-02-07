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


static f32 LOC_af32_SignalsParameters[3] = {0};  //Contains signals parameters acquired from ICU
static f32 LOC_af32_OldSignalsParameters[3] = {0};//Contains old signals parameters acquired from ICU used to differentiate if there is a change in fre or duty

static u8 LOC_u8_LastWaveLocation = 0;
/**
 * @brief Represents the buffer for the Scope that is used to shift between waved on wave at a time
 */
static PWM_t LOC_astr_ScopeBuffer[PWMSCOPE_MAX_DISPLAYED_SIGNALS] = {0};

/**
 * @brief It points to the first PWM wave in the array that the PWMScope screen refreshes from
 */
static u16 LOC_u16_Cursor = 0;

/**
 * @brief Pointer to the first free location in the buffer - 1 
 */
static u16 LOC_u16_WaveNumber = 0;

static u8 LOC_u8_FirstTrigger = True;



//APIs
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

    //Drawing PWM 0 initially
    enu_DrawPWM(LOC_af32_SignalsParameters);

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
            //Displaying Frequency in KHZ
            NOKIA5110_enu_DrawNumber(LOC_af32_SignalsParameters[0]/1000.0, 0, 30, NOKIA5110_BLACK_COLOUR);
            
            //Displaying Duty Ratio in %
            NOKIA5110_enu_DrawNumber(LOC_af32_SignalsParameters[1], 9, 30, NOKIA5110_BLACK_COLOUR);
            
            //Graphics
            if(LOC_u8_FirstTrigger)
            {
                enu_DrawPWM(LOC_af32_SignalsParameters);
                
                // LOC_u8_FirstTrigger = False;

            }
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
    // NOKIA5110_enu_DrawHorizontalLine(PWMSCOPE_X_AXIS_VERTICAL_SHIFT, PWMSCOPE_X_AXIS_HORIZOTAL_SHIFT, PWMSCOPE_X_AXIS_LENGTH, PWMSCOPE_X_AXIS_THICKNESS, PWMSCOPE_X_AXIS_COLOUR);
    NOKIA5110_enu_DrawVerticalLine(PWMSCOPE_Y_AXIS_VERTICAL_SHIFT, PWMSCOPE_Y_AXIS_HORIZOTAL_SHIFT, PWMSCOPE_Y_AXIS_HEIGHT, PWMSCOPE_Y_AXIS_THICKNESS, PWMSCOPE_Y_AXIS_COLOUR);

    //Drawing Arrows 
     NOKIA5110_enu_DrawCharacter(0x5E, PWMSCOPE_Y_AXIS_VERTICAL_SHIFT, PWMSCOPE_Y_AXIS_HORIZOTAL_SHIFT -2, PWMSCOPE_Y_AXIS_COLOUR, NOKIA5110_ENABLE_OVERLAP);
    // NOKIA5110_enu_DrawCharacter(0x3E, PWMSCOPE_X_AXIS_VERTICAL_SHIFT - 3, PWMSCOPE_X_AXIS_HORIZOTAL_SHIFT + 79, PWMSCOPE_X_AXIS_COLOUR, NOKIA5110_ENABLE_OVERLAP);

    //Drawing Scale
    
    return Local_u8_ErrorFlag;
}

static ErrorState_t enu_DrawPWM(f32* Copy_af32_SignalsParameters)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_af32_SignalsParameters)
    {

        u8 Local_u8_TonStartingPoint = 0, Local_Ton_EndingPoint = 0, Local_u8_TonLength = 0; //All in pixels
        u8 Local_u8_ToffStartingPoint = 0, Local_ToffEndingPoint = 0, Local_u8_ToffLength = 0; //All in pixels

        for (u8 Local_u8_WaveNumber = 0; Local_u8_WaveNumber <= 1; Local_u8_WaveNumber++)
        {
            Local_u8_TonStartingPoint = Local_u8_WaveNumber*PWMSCOPE_T_LENGTH + PWMSCOPE_Y_AXIS_HORIZOTAL_SHIFT;
            Local_u8_TonLength = ((Copy_af32_SignalsParameters[1]/100UL))*PWMSCOPE_T_LENGTH; // in pixels
            Local_u8_ToffStartingPoint = Local_u8_TonStartingPoint + Local_u8_TonLength;
            Local_u8_ToffLength = PWMSCOPE_T_LENGTH - Local_u8_TonLength -1;
            
            //Erasing Existig PWM wave
            NOKIA5110_enu_DrawFillRectangle(PWMSCOPE_5V_VERTICAL_SHIFT, Local_u8_TonStartingPoint + 1, PWMSCOPE_T_LENGTH, PWMSCOPE_X_AXIS_VERTICAL_SHIFT, NOKIA5110_WHITE_COLOUR);

            //Drawing Rising Edge
            if(Local_u8_TonLength != 0)
            {
                NOKIA5110_enu_DrawVerticalLine(PWMSCOPE_5V_VERTICAL_SHIFT, Local_u8_TonStartingPoint, 5*PWMSCOPE_Y_AXIS_SCALE, 1, NOKIA5110_BLACK_COLOUR);
            }
            
            //Drawing Ton portion
            NOKIA5110_enu_DrawHorizontalLine(PWMSCOPE_5V_VERTICAL_SHIFT, Local_u8_TonStartingPoint, Local_u8_TonLength, 1, NOKIA5110_BLACK_COLOUR);

            //Drawing Falling Edge
            if(Local_u8_TonLength != 0)
            {
                NOKIA5110_enu_DrawVerticalLine(PWMSCOPE_5V_VERTICAL_SHIFT, Local_u8_ToffStartingPoint, 5*PWMSCOPE_Y_AXIS_SCALE, 1, NOKIA5110_BLACK_COLOUR);
            }

            //Drawing Toff portion
            NOKIA5110_enu_DrawHorizontalLine(PWMSCOPE_X_AXIS_VERTICAL_SHIFT, Local_u8_ToffStartingPoint, Local_u8_ToffLength, 1, NOKIA5110_BLACK_COLOUR);
    
        }
        
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }
    
    return Local_u8_ErrorFlag;

}


/**
 * @brief To be done later
 * 
 */
// static ErrorState_t enu_GeneratePwmPattern(PWM_t Copy_str_Wave)
// {
//     u8 Local_u8_ErrorFlag = ES_NOK;
    
//     u8 Local_u8_NewPeriod = 0; 

//     //Check if a new period came
//     ICU_enu_GetState(&Local_u8_NewPeriod);

//     //It doesnt necessairly mean that only one period came but is a good approoximation
//     if(Local_u8_NewPeriod == ICU_SECOND_RISING_EDGE) 
//     {
//         //Calculate Starting and ending points(Assumes PWM waves are continous)

//         //Add Wave to Buffer
//         LOC_astr_ScopeBuffer[LOC_u16_Cursor] = Copy_str_Wave;



//         //Draw vertical lines

//         //Draw Horizontal Lines
//     }

//     return Local_u8_ErrorFlag;
// }