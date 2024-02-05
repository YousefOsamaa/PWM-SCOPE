#ifndef PCD8544_PRIVATE_H_
#define PCD8544_PRIVATE_H_



typedef struct 
{
    u8 DataPattern;
    u8 Y_Address;
    u8 X_Address;

}Data_t;

typedef struct 
{
    Data_t CharacterPatternArray[3];
    u8 Y_Address;
    u8 X_Address;

}Character_t;


//Addressing Modes
#define NOKIA5110_HORIZONTAL_ADDRESSING (0) 
#define NOKIA5110_VERTICAL_ADDRESSING   (1) 

//Power Modes
#define NOKIA5110_POWER_NORMAL_MODE     (0)     
#define NOKIA5110_POWER_DOWN_MODE       (1)

//Instruction sets
#define NOKIA5110_BASIC_IS              (0)
#define NOKIA5110_EXTENDED_IS           (1)

//Display Options
#define NOKIA5110_BLANK_DISPLAY         (0)
#define NOKIA5110_ALL_DISPLAY_ON        (1)
#define NOKIA5110_NORMAL_DISPLAY        (2)
#define NOKIA5110_INVERSE_VIDEO_DISPLAY (3)


//Temperature Control
#define NOKIA5110_TC0                  (0)     
#define NOKIA5110_TC1                  (1)
#define NOKIA5110_TC2                  (2)
#define NOKIA5110_TC3                  (3)


//Commands
#define NOKIA5110_FUNCTION_SET        (0)
#define NOKIA5110_DISPLAY_CONTROL     (1)
#define NOKIA5110_SET_Y_ADDRESS       (2)
#define NOKIA5110_SET_X_ADDRESS       (3)
#define NOKIA5110_TEMPERATURE_CONTOL  (4)
#define NOKIA5110_BIAS_SYSTEM         (5)
#define NOKIA5110_SET_VOP             (6)



//Constants
#define NOKIA5110_T_WL      (0.2)   //us
#define NOKIA5110_T_SU2     (0.2)   //us
#define NOKIA5110_T_WH2     (0.2)   //us  SCE MIN HIGH TIME
#define NOKIA5110_T_H2      (0.2)   //us  SCE HOLD TIME


//Frame Bits
#define NOKIA5110_B0        (0)
#define NOKIA5110_B1        (1)
#define NOKIA5110_B2        (2)
#define NOKIA5110_B3        (3)
#define NOKIA5110_B4        (4)
#define NOKIA5110_B5        (5)
#define NOKIA5110_B6        (6)
#define NOKIA5110_B7        (7)      

//Ranges of X and Y Addresses
#define NOKIA5110_X_MIN   (0)
#define NOKIA5110_X_MAX   (83)

#define NOKIA5110_Y_MIN   (0)
#define NOKIA5110_Y_MAX   (5)

//Ranges of X and Y coordiantes
#define NOKIA5110_X_COORDINATE_MIN   (NOKIA5110_X_MIN)
#define NOKIA5110_X_COORDINATE_MAX   (NOKIA5110_X_MAX)

#define NOKIA5110_Y_COORDINATE_MIN   (0)
#define NOKIA5110_Y_COORDINATE_MAX   (47)

//LCD Width and Length
#define NOKIA5110_LCD_LENGTH   (84)
#define NOKIA5110_LCD_WIDTH    (48)

//Colours
#define NOKIA5110_WHITE_COLOUR   (0) 
#define NOKIA5110_BLACK_COLOUR   (1)

//Character Sizes;



static ErrorState_t enu_PassByteToSPI(u8 Copy_u8_Byte);

static ErrorState_t enu_SendCommand(u8 Copy_u8_Command);

static ErrorState_t enu_SendData(u8 Copy_u8_Data);

static ErrorState_t enu_GenerateFrame(u8 Copy_u8_Command, u8* Copy_pu8_CommandFrame);

static ErrorState_t enu_ConvertCoordinatesToAddresses(u8* Copy_pu8_Y);

static ErrorState_t enu_DrawPixel(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour);

static ErrorState_t enu_ClearRAM();

static ErrorState_t enu_DrawASCII(u8 Copy_u8_ASCII, u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour);

static ErrorState_t enu_DrawFillRectangle(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Length, u8 Copy_u8_Width, u8 Copy_u8_Colour);

static ErrorState_t enu_DrawLine(u8 Copy_u8_Ystart, u8 Copy_u8_Xstart, u8 Copy_u8_Yend, u8 Copy_u8_Xend, u8 Copy_u8_Colour);

static ErrorState_t enu_DrawVerticalLine(u8 Copy_u8_Ystart, u8 Copy_u8_xStart, u8 Copy_u8_Height, u8 Copy_u8_Colour);

static ErrorState_t enu_DrawHorizontalLine(u8 Copy_u8_Ystart, u8 Copy_u8_xStart, u8 Copy_u8_Length, u8 Copy_u8_Colour);

#endif /* PCD8544_PRIVATE_H_ */