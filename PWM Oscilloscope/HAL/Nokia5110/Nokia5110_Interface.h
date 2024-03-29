#ifndef PCD8544_INTERFACE_H_
#define PCD8544_INTERFACE_H_


#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"

typedef struct 
{
    u8 DataPattern;
    u8 Y_Address;
    u8 X_Address;
    
}Data_t;

typedef struct 
{
    u8 CharacterToBeDrawn;
    u8 Y_Address;
    u8 X_Address;
    
}Character_t;

//Commands
#define NOKIA5110_FUNCTION_SET        (0)
#define NOKIA5110_DISPLAY_CONTROL     (1)
#define NOKIA5110_SET_Y_ADDRESS       (2)
#define NOKIA5110_SET_X_ADDRESS       (3)
#define NOKIA5110_TEMPERATURE_CONTOL  (4)
#define NOKIA5110_BIAS_SYSTEM         (5)
#define NOKIA5110_SET_VOP             (6)

//Display Modes
#define NOKIA5110_BLANK_DISPLAY         (0)
#define NOKIA5110_ALL_DISPLAY_ON        (1)
#define NOKIA5110_NORMAL_DISPLAY        (2)
#define NOKIA5110_INVERSE_VIDEO_DISPLAY (3)


//Instruction sets
#define NOKIA5110_BASIC_IS              (0)
#define NOKIA5110_EXTENDED_IS           (1)

//Power Modes
#define NOKIA5110_POWER_NORMAL_MODE     (0)     
#define NOKIA5110_POWER_DOWN_MODE       (1)

//Addressing Modes
#define NOKIA5110_HORIZONTAL_ADDRESSING (0) 
#define NOKIA5110_VERTICAL_ADDRESSING   (1) 

//Colours
#define NOKIA5110_WHITE_COLOUR   (0) 
#define NOKIA5110_BLACK_COLOUR   (1)

//Shifting Directions
#define NOKIA5110_SHIFT_VERTICAL       (0)
#define NOKIA5110_SHIFT_HORIZONTAL     (1)

//Ranges of X and Y Addresses
#define NOKIA5110_X_MIN   (0)
#define NOKIA5110_X_MAX   (83)

#define NOKIA5110_Y_MIN   (0)
#define NOKIA5110_Y_MAX   (5)

//Ranges of X and Y coordiantes
#define NOKIA5110_Y_COORDINATE_MIN   (0)
#define NOKIA5110_Y_COORDINATE_MAX   (47)

#define NOKIA5110_X_COORDINATE_MIN   (NOKIA5110_X_MIN)
#define NOKIA5110_X_COORDINATE_MAX   (NOKIA5110_X_MAX)


//LCD Width and Length
#define NOKIA5110_LCD_LENGTH   (84)
#define NOKIA5110_LCD_WIDTH    (48)

//Chsracter Overlapping
#define NOKIA5110_ENABLE_OVERLAP  (0) 
#define NOKIA5110_DISABLE_OVERLAP (1) 





extern ErrorState_t NOKIA5110_enu_Initialization(void);

extern ErrorState_t NOKIA5110_enu_SendCommand(u8 Copy_u8_Command);

extern ErrorState_t NOKIA5110_enu_SendData(u8 Copy_u8_Data);

extern ErrorState_t NOKIA5110_enu_GotoXY(u8 Copy_u8_X, u8 Copy_u8_Y);

extern ErrorState_t NOKIA5110_enu_SetAddressingMode(u8 Copy_u8_AddressingMode);

extern ErrorState_t NOKIA5110_enu_SetInstructionSetsAccess(u8 Copy_u8_InstructionSetAccess);

extern ErrorState_t NOKIA5110_enu_SetDisplayMode(u8 Copy_u8_DisplayMode);

extern ErrorState_t NOKIA5110_enu_Reset();

extern ErrorState_t NOKIA5110_enu_ClearScreen();

extern ErrorState_t NOKIA5110_enu_FillScreen();




//Graphical Library

extern ErrorState_t NOKIA5110_enu_DrawPixel(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour);

extern ErrorState_t NOKIA5110_enu_DrawCharacter(u8 Copy_u8_ASCII, u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour, u8 Copy_u8_Overlap);

extern ErrorState_t NOKIA5110_enu_DrawFillRectangle(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Length, u8 Copy_u8_Width, u8 Copy_u8_Colour);

extern ErrorState_t NOKIA5110_enu_DrawNumber(f32 Copy_f32_Number, u8 Copy_u8_Ystart, u8 Copy_u8_Xstart, u8 Copy_u8_Colour);

extern ErrorState_t NOKIA5110_enu_DrawPattern();

extern ErrorState_t NOKIA5110_enu_DrawLine(u8 Copy_u8_Ystart, u8 Copy_u8_Xstart, u8 Copy_u8_Yend, u8 Copy_u8_Xend, u8 Copy_u8_Thickness, u8 Copy_u8_Colour);

extern ErrorState_t NOKIA5110_enu_DrawVerticalLine(u8 Copy_u8_Ystart, u8 Copy_u8_xStart, u8 Copy_u8_Height, u8 Copy_u8_Thcickness, u8 Copy_u8_Colour);

extern ErrorState_t NOKIA5110_enu_DrawHorizontalLine(u8 Copy_u8_Ystart, u8 Copy_u8_xStart, u8 Copy_u8_Length, u8 Copy_u8_Thcickness, u8 Copy_u8_Colour);

extern ErrorState_t NOKIA5110_enu_ShiftPixel(u8 Copy_u8_Y, u8 Copy_u8_X, s32 Copy_s32_ShiftMagnitude, u8 Copy_u8_Direction);

extern ErrorState_t NOKIA5110_enu_CopyPixelByShifting(u8 Copy_u8_Y, u8 Copy_u8_X, s32 Copy_s32_ShiftMagnitude, u8 Copy_u8_Direction);

extern ErrorState_t NOKIA5110_enu_CopyPixelByCooridnates(u8 Copy_u8_Yoriginal, u8 Copy_u8_Xoriginal, u8 Copy_u8_Ycopied, u8 Copy_u8_Xcopied);

extern ErrorState_t NOKIA5110_enu_DrawString(const u8* Copy_pu8_StringArray, u8 Copy_u8_Ystart, u8 Copy_u8_Xstart, u8 Copy_u8_Colour);






#endif /* PCD8544_INTERFACE_H_ */