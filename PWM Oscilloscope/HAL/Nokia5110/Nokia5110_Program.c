#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/SPI/SPI_Interface.h"

#include "Nokia5110_Config.h"
#include "Nokia5110_Private.h"


//A Nokia5110_t object that holds it current properties
extern NOKIA5110_t Mod_str_Nokia5110Configurations;


//LCD Buffer
static u8 LOC_au8_BufferArray[NOKIA5110_Y_MAX + 1][NOKIA5110_X_MAX + 1] = {0};

//ASCII Characters Array (5 x 7)
static const u8 LOC_u8_ASCII[]  = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x5B, 0x4F, 0x5B, 0x3E, 0x3E, 0x6B,
    0x4F, 0x6B, 0x3E, 0x1C, 0x3E, 0x7C, 0x3E, 0x1C, 0x18, 0x3C, 0x7E, 0x3C,
    0x18, 0x1C, 0x57, 0x7D, 0x57, 0x1C, 0x1C, 0x5E, 0x7F, 0x5E, 0x1C, 0x00,
    0x18, 0x3C, 0x18, 0x00, 0xFF, 0xE7, 0xC3, 0xE7, 0xFF, 0x00, 0x18, 0x24,
    0x18, 0x00, 0xFF, 0xE7, 0xDB, 0xE7, 0xFF, 0x30, 0x48, 0x3A, 0x06, 0x0E,
    0x26, 0x29, 0x79, 0x29, 0x26, 0x40, 0x7F, 0x05, 0x05, 0x07, 0x40, 0x7F,
    0x05, 0x25, 0x3F, 0x5A, 0x3C, 0xE7, 0x3C, 0x5A, 0x7F, 0x3E, 0x1C, 0x1C,
    0x08, 0x08, 0x1C, 0x1C, 0x3E, 0x7F, 0x14, 0x22, 0x7F, 0x22, 0x14, 0x5F,
    0x5F, 0x00, 0x5F, 0x5F, 0x06, 0x09, 0x7F, 0x01, 0x7F, 0x00, 0x66, 0x89,
    0x95, 0x6A, 0x60, 0x60, 0x60, 0x60, 0x60, 0x94, 0xA2, 0xFF, 0xA2, 0x94,
    0x08, 0x04, 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x20, 0x10, 0x08, 0x08,
    0x2A, 0x1C, 0x08, 0x08, 0x1C, 0x2A, 0x08, 0x08, 0x1E, 0x10, 0x10, 0x10,
    0x10, 0x0C, 0x1E, 0x0C, 0x1E, 0x0C, 0x30, 0x38, 0x3E, 0x38, 0x30, 0x06,
    0x0E, 0x3E, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5F,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14,
    0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x23, 0x13, 0x08, 0x64, 0x62, 0x36, 0x49,
    0x56, 0x20, 0x50, 0x00, 0x08, 0x07, 0x03, 0x00, 0x00, 0x1C, 0x22, 0x41,
    0x00, 0x00, 0x41, 0x22, 0x1C, 0x00, 0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x08,
    0x08, 0x3E, 0x08, 0x08, 0x00, 0x80, 0x70, 0x30, 0x00, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x00, 0x00, 0x60, 0x60, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x72, 0x49,
    0x49, 0x49, 0x46, 0x21, 0x41, 0x49, 0x4D, 0x33, 0x18, 0x14, 0x12, 0x7F,
    0x10, 0x27, 0x45, 0x45, 0x45, 0x39, 0x3C, 0x4A, 0x49, 0x49, 0x31, 0x41,
    0x21, 0x11, 0x09, 0x07, 0x36, 0x49, 0x49, 0x49, 0x36, 0x46, 0x49, 0x49,
    0x29, 0x1E, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x40, 0x34, 0x00, 0x00,
    0x00, 0x08, 0x14, 0x22, 0x41, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x41,
    0x22, 0x14, 0x08, 0x02, 0x01, 0x59, 0x09, 0x06, 0x3E, 0x41, 0x5D, 0x59,
    0x4E, 0x7C, 0x12, 0x11, 0x12, 0x7C, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x3E,
    0x41, 0x41, 0x41, 0x22, 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x7F, 0x49, 0x49,
    0x49, 0x41, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x3E, 0x41, 0x41, 0x51, 0x73,
    0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x41, 0x7F, 0x41, 0x00, 0x20, 0x40,
    0x41, 0x3F, 0x01, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x7F, 0x40, 0x40, 0x40,
    0x40, 0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x3E,
    0x41, 0x41, 0x41, 0x3E, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x3E, 0x41, 0x51,
    0x21, 0x5E, 0x7F, 0x09, 0x19, 0x29, 0x46, 0x26, 0x49, 0x49, 0x49, 0x32,
    0x03, 0x01, 0x7F, 0x01, 0x03, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x1F, 0x20,
    0x40, 0x20, 0x1F, 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x63, 0x14, 0x08, 0x14,
    0x63, 0x03, 0x04, 0x78, 0x04, 0x03, 0x61, 0x59, 0x49, 0x4D, 0x43, 0x00,
    0x7F, 0x41, 0x41, 0x41, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x41, 0x41,
    0x41, 0x7F, 0x04, 0x02, 0x01, 0x02, 0x04, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x00, 0x03, 0x07, 0x08, 0x00, 0x20, 0x54, 0x54, 0x78, 0x40, 0x7F, 0x28,
    0x44, 0x44, 0x38, 0x38, 0x44, 0x44, 0x44, 0x28, 0x38, 0x44, 0x44, 0x28,
    0x7F, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00, 0x08, 0x7E, 0x09, 0x02, 0x18,
    0xA4, 0xA4, 0x9C, 0x78, 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x44, 0x7D,
    0x40, 0x00, 0x20, 0x40, 0x40, 0x3D, 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,
    0x00, 0x41, 0x7F, 0x40, 0x00, 0x7C, 0x04, 0x78, 0x04, 0x78, 0x7C, 0x08,
    0x04, 0x04, 0x78, 0x38, 0x44, 0x44, 0x44, 0x38, 0xFC, 0x18, 0x24, 0x24,
    0x18, 0x18, 0x24, 0x24, 0x18, 0xFC, 0x7C, 0x08, 0x04, 0x04, 0x08, 0x48,
    0x54, 0x54, 0x54, 0x24, 0x04, 0x04, 0x3F, 0x44, 0x24, 0x3C, 0x40, 0x40,
    0x20, 0x7C, 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x3C, 0x40, 0x30, 0x40, 0x3C,
    0x44, 0x28, 0x10, 0x28, 0x44, 0x4C, 0x90, 0x90, 0x90, 0x7C, 0x44, 0x64,
    0x54, 0x4C, 0x44, 0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 0x00, 0x77, 0x00,
    0x00, 0x00, 0x41, 0x36, 0x08, 0x00, 0x02, 0x01, 0x02, 0x04, 0x02, 0x3C,
    0x26, 0x23, 0x26, 0x3C, 0x1E, 0xA1, 0xA1, 0x61, 0x12, 0x3A, 0x40, 0x40,
    0x20, 0x7A, 0x38, 0x54, 0x54, 0x55, 0x59, 0x21, 0x55, 0x55, 0x79, 0x41,
    0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
    0x21, 0x55, 0x54, 0x78, 0x40, 0x20, 0x54, 0x55, 0x79, 0x40, 0x0C, 0x1E,
    0x52, 0x72, 0x12, 0x39, 0x55, 0x55, 0x55, 0x59, 0x39, 0x54, 0x54, 0x54,
    0x59, 0x39, 0x55, 0x54, 0x54, 0x58, 0x00, 0x00, 0x45, 0x7C, 0x41, 0x00,
    0x02, 0x45, 0x7D, 0x42, 0x00, 0x01, 0x45, 0x7C, 0x40, 0x7D, 0x12, 0x11,
    0x12, 0x7D, // A-umlaut
    0xF0, 0x28, 0x25, 0x28, 0xF0, 0x7C, 0x54, 0x55, 0x45, 0x00, 0x20, 0x54,
    0x54, 0x7C, 0x54, 0x7C, 0x0A, 0x09, 0x7F, 0x49, 0x32, 0x49, 0x49, 0x49,
    0x32, 0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
    0x32, 0x4A, 0x48, 0x48, 0x30, 0x3A, 0x41, 0x41, 0x21, 0x7A, 0x3A, 0x42,
    0x40, 0x20, 0x78, 0x00, 0x9D, 0xA0, 0xA0, 0x7D, 0x3D, 0x42, 0x42, 0x42,
    0x3D, // O-umlaut
    0x3D, 0x40, 0x40, 0x40, 0x3D, 0x3C, 0x24, 0xFF, 0x24, 0x24, 0x48, 0x7E,
    0x49, 0x43, 0x66, 0x2B, 0x2F, 0xFC, 0x2F, 0x2B, 0xFF, 0x09, 0x29, 0xF6,
    0x20, 0xC0, 0x88, 0x7E, 0x09, 0x03, 0x20, 0x54, 0x54, 0x79, 0x41, 0x00,
    0x00, 0x44, 0x7D, 0x41, 0x30, 0x48, 0x48, 0x4A, 0x32, 0x38, 0x40, 0x40,
    0x22, 0x7A, 0x00, 0x7A, 0x0A, 0x0A, 0x72, 0x7D, 0x0D, 0x19, 0x31, 0x7D,
    0x26, 0x29, 0x29, 0x2F, 0x28, 0x26, 0x29, 0x29, 0x29, 0x26, 0x30, 0x48,
    0x4D, 0x40, 0x20, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x38, 0x2F, 0x10, 0xC8, 0xAC, 0xBA, 0x2F, 0x10, 0x28, 0x34, 0xFA, 0x00,
    0x00, 0x7B, 0x00, 0x00, 0x08, 0x14, 0x2A, 0x14, 0x22, 0x22, 0x14, 0x2A,
    0x14, 0x08, 0x55, 0x00, 0x55, 0x00, 0x55, // #176 (25% block) missing in old// code
    0xAA, 0x55, 0xAA, 0x55, 0xAA,             // 50% block
    0xFF, 0x55, 0xFF, 0x55, 0xFF,             // 75% block
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x10, 0x10, 0x10, 0xFF, 0x00, 0x14, 0x14,
    0x14, 0xFF, 0x00, 0x10, 0x10, 0xFF, 0x00, 0xFF, 0x10, 0x10, 0xF0, 0x10,
    0xF0, 0x14, 0x14, 0x14, 0xFC, 0x00, 0x14, 0x14, 0xF7, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x14, 0x14, 0xF4, 0x04, 0xFC, 0x14, 0x14, 0x17,
    0x10, 0x1F, 0x10, 0x10, 0x1F, 0x10, 0x1F, 0x14, 0x14, 0x14, 0x1F, 0x00,
    0x10, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10,
    0x10, 0x1F, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x10, 0x00, 0x00, 0x00, 0xFF,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFF, 0x10, 0x00,
    0x00, 0x00, 0xFF, 0x14, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x1F,
    0x10, 0x17, 0x00, 0x00, 0xFC, 0x04, 0xF4, 0x14, 0x14, 0x17, 0x10, 0x17,
    0x14, 0x14, 0xF4, 0x04, 0xF4, 0x00, 0x00, 0xFF, 0x00, 0xF7, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0xF7, 0x00, 0xF7, 0x14, 0x14, 0x14, 0x17,
    0x14, 0x10, 0x10, 0x1F, 0x10, 0x1F, 0x14, 0x14, 0x14, 0xF4, 0x14, 0x10,
    0x10, 0xF0, 0x10, 0xF0, 0x00, 0x00, 0x1F, 0x10, 0x1F, 0x00, 0x00, 0x00,
    0x1F, 0x14, 0x00, 0x00, 0x00, 0xFC, 0x14, 0x00, 0x00, 0xF0, 0x10, 0xF0,
    0x10, 0x10, 0xFF, 0x10, 0xFF, 0x14, 0x14, 0x14, 0xFF, 0x14, 0x10, 0x10,
    0x10, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x10, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x38, 0x44, 0x44,
    0x38, 0x44, 0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
    0x7E, 0x02, 0x02, 0x06, 0x06, 0x02, 0x7E, 0x02, 0x7E, 0x02, 0x63, 0x55,
    0x49, 0x41, 0x63, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x40, 0x7E, 0x20, 0x1E,
    0x20, 0x06, 0x02, 0x7E, 0x02, 0x02, 0x99, 0xA5, 0xE7, 0xA5, 0x99, 0x1C,
    0x2A, 0x49, 0x2A, 0x1C, 0x4C, 0x72, 0x01, 0x72, 0x4C, 0x30, 0x4A, 0x4D,
    0x4D, 0x30, 0x30, 0x48, 0x78, 0x48, 0x30, 0xBC, 0x62, 0x5A, 0x46, 0x3D,
    0x3E, 0x49, 0x49, 0x49, 0x00, 0x7E, 0x01, 0x01, 0x01, 0x7E, 0x2A, 0x2A,
    0x2A, 0x2A, 0x2A, 0x44, 0x44, 0x5F, 0x44, 0x44, 0x40, 0x51, 0x4A, 0x44,
    0x40, 0x40, 0x44, 0x4A, 0x51, 0x40, 0x00, 0x00, 0xFF, 0x01, 0x03, 0xE0,
    0x80, 0xFF, 0x00, 0x00, 0x08, 0x08, 0x6B, 0x6B, 0x08, 0x36, 0x12, 0x36,
    0x24, 0x36, 0x06, 0x0F, 0x09, 0x0F, 0x06, 0x00, 0x00, 0x18, 0x18, 0x00,
    0x00, 0x00, 0x10, 0x10, 0x00, 0x30, 0x40, 0xFF, 0x01, 0x01, 0x00, 0x1F,
    0x01, 0x01, 0x1E, 0x00, 0x19, 0x1D, 0x17, 0x12, 0x00, 0x3C, 0x3C, 0x3C,
    0x3C, 0x00, 0x00, 0x00, 0x00, 0x00 // #255 NBSP
};


extern ErrorState_t NOKIA5110_enu_Initialization(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK, Local_u8_GeneratedFrame;


    //DIO AND SPI Initialization
    DIO_enu_SetPinDiretion(NOKIA5110_SDIN_GROUP, NOKIA5110_SDIN_PIN, DIO_PIN_WRITE); //Configuring SDIN(MOSI) pin as output
    
    DIO_enu_SetPinDiretion(NOKIA5110_SCLK_GROUP, NOKIA5110_SCLK_PIN, DIO_PIN_WRITE); //Configuring SCLK(SCK) pin as output
    
    DIO_enu_SetPinValue(NOKIA5110_SCE_GROUP, NOKIA5110_SCE_PIN, DIO_HIGH); //Placing a High on  SCE(SS) pin 
    DIO_enu_SetPinDiretion(NOKIA5110_SCE_GROUP, NOKIA5110_SCE_PIN, DIO_PIN_WRITE); //Configuring SCE(SS) pin as output
    
    
    DIO_enu_SetPinValue(NOKIA5110_RES_GROUP, NOKIA5110_RES_PIN, DIO_HIGH); //Placing a High on  RES pin 
    DIO_enu_SetPinDiretion(NOKIA5110_RES_GROUP, NOKIA5110_RES_PIN, DIO_PIN_WRITE); //Configuring RES pin as output
    
    DIO_enu_SetPinDiretion(NOKIA5110_DC_GROUP, NOKIA5110_DC_PIN, DIO_PIN_WRITE); //Configuring DC pin as output

    SPI_enu_Initialization(); //Initialzing SPI Module

    
    //Reset
    DIO_enu_SetPinValue(NOKIA5110_SCE_GROUP, NOKIA5110_SCE_PIN, DIO_LOW); //Placing a Low on  SCE(SS) pin 
	DIO_enu_SetPinState(NOKIA5110_RES_GROUP, NOKIA5110_RES_PIN, DIO_LOW); //Applying Reset Order
	
	_delay_us(NOKIA5110_T_WL); //Delay needed for a reset

	DIO_enu_SetPinState(NOKIA5110_RES_GROUP, NOKIA5110_RES_PIN, DIO_HIGH); //Removing Reset Order 
        
	//Function Set
    enu_GenerateFrame(NOKIA5110_FUNCTION_SET, &Local_u8_GeneratedFrame); //Generating Command Frame
    enu_PassByteToSPI(Local_u8_GeneratedFrame);

    //Display Control
    enu_GenerateFrame(NOKIA5110_DISPLAY_CONTROL, &Local_u8_GeneratedFrame); //Generating Command Frame
    enu_PassByteToSPI(Local_u8_GeneratedFrame);


    //Switching to Extended Instruction Set
    Mod_str_Nokia5110Configurations.InstructionSetAccess = NOKIA5110_EXTENDED_IS; //Setting H 
    enu_GenerateFrame(NOKIA5110_FUNCTION_SET, &Local_u8_GeneratedFrame); //Generating Command Frame
    enu_PassByteToSPI(Local_u8_GeneratedFrame);

    //Temperature Control
    enu_GenerateFrame(NOKIA5110_TEMPERATURE_CONTOL, &Local_u8_GeneratedFrame); //Generating Command Frame
    enu_PassByteToSPI(Local_u8_GeneratedFrame);

    //Bias Value
    enu_GenerateFrame(NOKIA5110_BIAS_SYSTEM, &Local_u8_GeneratedFrame); //Generating Command Frame
    enu_PassByteToSPI(Local_u8_GeneratedFrame);
 
    //Vop 
    enu_GenerateFrame(NOKIA5110_SET_VOP, &Local_u8_GeneratedFrame); //Generating Command Frame
    enu_PassByteToSPI(Local_u8_GeneratedFrame);

    //Returning to Basic IS
    Mod_str_Nokia5110Configurations.InstructionSetAccess = NOKIA5110_BASIC_IS; //Cearing H
    enu_GenerateFrame(NOKIA5110_FUNCTION_SET, &Local_u8_GeneratedFrame); //Generating Command Frame
    enu_PassByteToSPI(Local_u8_GeneratedFrame);
    

 
    return Local_u8_ErrorFlag; 
}

extern ErrorState_t NOKIA5110_enu_SendCommand(u8 Copy_u8_Command)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    Local_u8_ErrorFlag = enu_SendCommand(Copy_u8_Command);

    return Local_u8_ErrorFlag;
}

extern ErrorState_t NOKIA5110_enu_SendData(u8 Copy_u8_Data)
{ 
    u8 Local_u8_ErrorFlag = ES_NOK;

    Local_u8_ErrorFlag = enu_SendData(Copy_u8_Data);

    return Local_u8_ErrorFlag;
	
}

extern ErrorState_t NOKIA5110_enu_GotoXY(u8 Copy_u8_Y, u8 Copy_u8_X)
{
    u8 Local_u8_ErrorFlag = ES_NOK, Local_u8_GeneratedFrame;

    if((Copy_u8_X >= NOKIA5110_X_MIN && Copy_u8_X <= NOKIA5110_X_MAX) && (Copy_u8_Y >= NOKIA5110_Y_MIN && Copy_u8_Y <= NOKIA5110_Y_MAX))
    {
        Mod_str_Nokia5110Configurations.X_Address = Copy_u8_X;
        Mod_str_Nokia5110Configurations.Y_Address = Copy_u8_Y;

        DIO_enu_SetPinValue(NOKIA5110_DC_GROUP, NOKIA5110_DC_PIN, DIO_LOW); //Placing low on DC pin to send command

        //Sending Y address
        enu_GenerateFrame(NOKIA5110_SET_Y_ADDRESS, &Local_u8_GeneratedFrame);
        enu_PassByteToSPI(Local_u8_GeneratedFrame);
        //Sending X address
        enu_GenerateFrame(NOKIA5110_SET_X_ADDRESS, &Local_u8_GeneratedFrame);
        enu_PassByteToSPI(Local_u8_GeneratedFrame);

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }


    return Local_u8_ErrorFlag;
}

extern ErrorState_t NOKIA5110_enu_SetAddressingMode(u8 Copy_u8_AddressingMode)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_u8_AddressingMode == NOKIA5110_HORIZONTAL_ADDRESSING || Copy_u8_AddressingMode == NOKIA5110_VERTICAL_ADDRESSING)
    {
        Mod_str_Nokia5110Configurations.AddressingMode = Copy_u8_AddressingMode;

        Local_u8_ErrorFlag = enu_SendCommand(NOKIA5110_FUNCTION_SET);

    }
    else
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }

    return Local_u8_ErrorFlag;
}

extern ErrorState_t NOKIA5110_enu_SetInstructionSetsAccess(u8 Copy_u8_InstructionSetAccess)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_u8_InstructionSetAccess == NOKIA5110_BASIC_IS || Copy_u8_InstructionSetAccess == NOKIA5110_EXTENDED_IS)
    {
        Mod_str_Nokia5110Configurations.InstructionSetAccess = Copy_u8_InstructionSetAccess;
        
        Local_u8_ErrorFlag = enu_SendCommand(NOKIA5110_FUNCTION_SET);
    }
    else
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }

    return Local_u8_ErrorFlag;

}

extern ErrorState_t NOKIA5110_enu_SetDisplayMode(u8 Copy_u8_DisplayMode)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if((Copy_u8_DisplayMode == NOKIA5110_BLANK_DISPLAY) || (Copy_u8_DisplayMode == NOKIA5110_ALL_DISPLAY_ON) || (Copy_u8_DisplayMode == NOKIA5110_NORMAL_DISPLAY) || (Copy_u8_DisplayMode == NOKIA5110_INVERSE_VIDEO_DISPLAY))
    {
        Mod_str_Nokia5110Configurations.DisplayControlMode = Copy_u8_DisplayMode;

        Local_u8_ErrorFlag = enu_SendCommand(NOKIA5110_DISPLAY_CONTROL);
    }
    else
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }
    
    return Local_u8_ErrorFlag;
}

/**
 * @brief  Clears LCD and Ram and resets the LCD driver registers
 * 
 * @return ErrorState_t 
 */
extern ErrorState_t NOKIA5110_enu_Reset()
{
    u8 Local_u8_ErrorFlag = ES_OK;

    //Clearing RAM
    enu_ClearRAM();

    //Reset
    DIO_enu_SetPinValue(NOKIA5110_SCE_GROUP, NOKIA5110_SCE_PIN, DIO_LOW); //Placing a Low on  SCE(SS) pin 
	DIO_enu_SetPinState(NOKIA5110_RES_GROUP, NOKIA5110_RES_PIN, DIO_LOW); //Applying Reset Order
	
	_delay_us(NOKIA5110_T_WL); //Delay needed for a reset

	DIO_enu_SetPinState(NOKIA5110_RES_GROUP, NOKIA5110_RES_PIN, DIO_HIGH); //Removing Reset Order 

    
    return Local_u8_ErrorFlag;
}

/**
 * @brief Clears LCD screen and Buffer
 * 
 * @return ErrorState_t 
 */
extern ErrorState_t NOKIA5110_enu_ClearScreen()
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    enu_ClearRAM();

    return Local_u8_ErrorFlag;
}

//Graphical Library
/**
 * @brief Draws a pixel at the given coordinates with the given colour
 * 
 * @param Copy_u8_Y y-coordinate
 * @param Copy_u8_X x-coordinate
 * @param Copy_u8_Colour Colour (black or white)
 * @return ErrorState_t 
 */
extern ErrorState_t NOKIA5110_enu_DrawPixel(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour)
{
    u8 Local_u8_ErrorFlag = ES_NOK;


    Local_u8_ErrorFlag = enu_DrawPixel(Copy_u8_Y, Copy_u8_X, Copy_u8_Colour);

    return Local_u8_ErrorFlag;
}

/**
 * @brief Draws an ASCII Character as a 8 x 5 character @ Magnification = 1, it erases any pattern found on its character block
 * 
 * @param Copy_u8_ASCII ASCII code (255)
 * @param Copy_u8_Y y-coordinate of the top left corner
 * @param Copy_u8_X x-coordinate of the top left corner
 * @param Copy_u8_Colour Colour 
 * @param Copy_u8_YMagnification Magnification in the X direction 
 * @param Copy_u8_XMagnification Magnification in the Y directtion
 * @return ErrorState_t 
 */
extern ErrorState_t NOKIA5110_enu_DrawCharacter(u8 Copy_u8_ASCII, u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

   Local_u8_ErrorFlag = enu_DrawASCII(Copy_u8_ASCII, Copy_u8_Y, Copy_u8_X, NOKIA5110_BLACK_COLOUR);

    return Local_u8_ErrorFlag;
}

/**
 * @brief Draws a filled rectangle at the specified area
 * 
 * @param Copy_u8_Y y-coordinate of the top left corner
 * @param Copy_u8_X y-coordinate of the top left corner
 * @param Copy_u8_Length rectangle's length (in the direction of the x - axis)
 * @param Copy_u8_Width rectangle's width (in the direction of the y - axis)
 * @return ErrorState_t 
 */
extern ErrorState_t NOKIA5110_enu_DrawFillRectangle(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Length, u8 Copy_u8_Width, u8 Copy_u8_Colour)
{
    u8 Local_u8_ErrorFlag =ES_NOK;

    Local_u8_ErrorFlag = enu_DrawRectangle(Copy_u8_Y, Copy_u8_X, Copy_u8_Length, Copy_u8_Width, Copy_u8_Colour);

    return Local_u8_ErrorFlag;
}

extern ErrorState_t NOKIA5110_enu_DrawNumber()
{
    u8 Local_u8_ErrorFlag = ES_NOK;


    return Local_u8_ErrorFlag;
}

extern ErrorState_t NOKIA5110_enu_DrawPattern()
{
    u8 Local_u8_ErrorFlag = ES_NOK;


    return Local_u8_ErrorFlag;
}
/**
 * @brief Draws a line using Bresenham's Algorithm using only integer arithmetic for fast operation 
 * 
 * @param Copy_u8_Ystart starting y - coordinate
 * @param Copy_u8_Xstart starting x - coordinate
 * @param Copy_u8_Yend  ending y - coordinate
 * @param Copy_u8_Xend  ending x - coordinate
 * @return ErrorState_t 
 */
extern ErrorState_t NOKIA5110_enu_DrawLine(u8 Copy_u8_Ystart, u8 Copy_u8_Xstart, u8 Copy_u8_Yend, u8 Copy_u8_Xend)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    u8 Local_u8_dx = 0; //delta x 
    u8 Local_u8_dy = 0; //delta y 
    u8 Local_u8_D = 0; //error 
    u8 Local_u8_x = 0, Local_u8_y = 0; //Graphing counters

    Local_u8_dx = Copy_u8_Xend - Copy_u8_Xstart;
    Local_u8_dy = Copy_u8_Yend - Copy_u8_Ystart;

    if(!Local_u8_dx) //if the line is horizontal
    {
    }
    else if(!Local_u8_dy)//if the line is vertical
    {
        // Gener
        // enu_DrawVerticalLine(Copy_u8_Ystart, Copy_u8_Xstart, );
    }
    else //line has a slope
    {
        enu_DrawLine(Copy_u8_Ystart, Copy_u8_Xstart, Copy_u8_Yend, Copy_u8_Xend);
    }
}


//Local Functions
/**
 * @brief Passes needed data to the SPI module to transmit it to the LCD after making shure that the SPI was available to prevent WCOL
 * 
 * @param Copy_u8_Byte Transmitted Byte
 * @return ErrorState_t 
 */
static ErrorState_t enu_PassByteToSPI(u8 Copy_u8_Byte)
{
    u8 Local_u8_StateSPI, Local_u8_ErrorFlag = ES_NOK;

    SPI_enu_GetCommState(&Local_u8_StateSPI); //Checking for SPI state

    if(Local_u8_StateSPI == SPI_FREE)
    {
        DIO_enu_SetPinValue(NOKIA5110_SCE_GROUP, NOKIA5110_SCE_PIN, DIO_LOW); //Holding Chip Enable pin low to dtart communication

        _delay_us(NOKIA5110_T_WL); //SCE SET-UP TIME

        SPI_enu_MasterSend(Copy_u8_Byte); //Sending value
         
        _delay_us(NOKIA5110_T_H2); //SCE HOLD TIME

        DIO_enu_SetPinValue(NOKIA5110_SCE_GROUP, NOKIA5110_SCE_PIN, DIO_HIGH); //Placing high on Chip enable pin to stop communication

        _delay_us(NOKIA5110_T_WH2); //SCE MIN HIGH TIME

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_WAIT; //When the SPI is busy
    }

    return Local_u8_ErrorFlag;
}

/**
 * @brief Sends a specific Command depending on the LCD object set c/cs
 * 
 * @param Copy_u8_Command Command from the LCD's Instruction Set
 * @return ErrorState_t 
 */
static ErrorState_t enu_SendCommand(u8 Copy_u8_Command)
{
    u8 Local_u8_ErrorFlag = ES_NOK, Local_u8_GeneratedFrame;

    enu_GenerateFrame(Copy_u8_Command, &Local_u8_GeneratedFrame); //Frame Generation

    DIO_enu_SetPinValue(NOKIA5110_DC_GROUP, NOKIA5110_DC_PIN, DIO_LOW); //Placing low on DC pin to send command

    Local_u8_ErrorFlag = enu_PassByteToSPI(Local_u8_GeneratedFrame); //Sending Command

    return Local_u8_ErrorFlag;     
	
}

/**
 * @brief Sends A Data frame to the LCD
 * 
 * @param Copy_u8_Data Given Data Frame
 * @return ErrorState_t 
 */
static ErrorState_t enu_SendData(u8 Copy_u8_Data)
{
	u8 Local_u8_ErrorFlag = ES_NOK;
	
	DIO_enu_SetPinValue(NOKIA5110_DC_GROUP, NOKIA5110_DC_PIN, DIO_HIGH); //Placing high on DC pin to send data

	Local_u8_ErrorFlag = enu_PassByteToSPI(Copy_u8_Data);

	return Local_u8_ErrorFlag;
}

/**
 * @brief Generates needed Frame for a specific instruction set depending on the LCD object c/cs
 * 
 * @param Copy_u8_Command  Needed instruction set
 * @param Copy_pu8_CommandFrame A pointer to character to place the frame in
 * @return ErrorState_t 
 */
static ErrorState_t enu_GenerateFrame(u8 Copy_u8_Command, u8* Copy_pu8_CommandFrame)
{
    
    u8 Local_u8_ErrorFlag = ES_NOK;

    *Copy_pu8_CommandFrame = 0; //Masking the variable with zeroes

    switch (Copy_u8_Command)
    {
        case NOKIA5110_FUNCTION_SET:
        {
            u8 Local_u8_PD = Mod_str_Nokia5110Configurations.PowerMode;
            u8 Local_u8_V = Mod_str_Nokia5110Configurations.AddressingMode;
            u8 Local_u8_H = Mod_str_Nokia5110Configurations.InstructionSetAccess;

            //Generating Command frame based on LCD configuration found in Mod_str_Nokia5110Configuration 
            *Copy_pu8_CommandFrame  |= (1 << NOKIA5110_B5) | (Local_u8_PD << NOKIA5110_B2) |(Local_u8_V << NOKIA5110_B1) | (Local_u8_H << NOKIA5110_B0);
            
            Local_u8_ErrorFlag = ES_OK;
            break;
        }

        case NOKIA5110_DISPLAY_CONTROL:
        {
            u8 Local_u8_DisplayControl = Mod_str_Nokia5110Configurations.DisplayControlMode;
            u8 Local_u8_D = 0, Local_u8_E = 0;

            if(Local_u8_DisplayControl == NOKIA5110_BLANK_DISPLAY)
            {
                //Bits already contain 0 0
                Local_u8_ErrorFlag = ES_OK;
            }
            else if(Local_u8_DisplayControl == NOKIA5110_ALL_DISPLAY_ON )
            {
                //D already contains 0
                Local_u8_E = 1;
                Local_u8_ErrorFlag = ES_OK;
            }
            else if(Local_u8_DisplayControl == NOKIA5110_NORMAL_DISPLAY)
            {
                Local_u8_D = 1;
                //E already contains 0
                Local_u8_ErrorFlag = ES_OK;
            }
            else if(Local_u8_DisplayControl == NOKIA5110_INVERSE_VIDEO_DISPLAY)
            {
                Local_u8_D = 1;
                Local_u8_E = 1;
                Local_u8_ErrorFlag = ES_OK;
            }
            else
            {
                Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
            }

            //if a non correct configuration is used 0x00 frame is sent
            if(Local_u8_ErrorFlag == ES_OK)
            {
                *Copy_pu8_CommandFrame = (1 << NOKIA5110_B3) | (Local_u8_D << NOKIA5110_B2) | (Local_u8_E << NOKIA5110_B0);
            }

            break;
        }

        case NOKIA5110_SET_Y_ADDRESS:
        {
            u8 Local_u8_YAddress = Mod_str_Nokia5110Configurations.Y_Address;
            
            *Copy_pu8_CommandFrame = Local_u8_YAddress;

            *Copy_pu8_CommandFrame |= (1 << NOKIA5110_B6);

            Local_u8_ErrorFlag = ES_OK;
            break;
        }

        case NOKIA5110_SET_X_ADDRESS:
        {
            u8 Local_u8_XAddress = Mod_str_Nokia5110Configurations.X_Address;
            
            *Copy_pu8_CommandFrame = Local_u8_XAddress;

            *Copy_pu8_CommandFrame |= (1 << NOKIA5110_B7);

            Local_u8_ErrorFlag = ES_OK;
            break;
        }

        case NOKIA5110_TEMPERATURE_CONTOL:
        {
            u8 Local_u8_TC = Mod_str_Nokia5110Configurations.TemperatureCoefficient;

            *Copy_pu8_CommandFrame = Local_u8_TC;
            
            *Copy_pu8_CommandFrame |= (1 << NOKIA5110_B2);

            Local_u8_ErrorFlag = ES_OK;
            break;
        }

        case NOKIA5110_BIAS_SYSTEM:
        {
            //To be done later
            u8 Local_u8_BiasValue = Mod_str_Nokia5110Configurations.BiasValue;
            
            *Copy_pu8_CommandFrame = Local_u8_BiasValue;

            *Copy_pu8_CommandFrame |= (1 << NOKIA5110_B4);

            Local_u8_ErrorFlag = ES_OK;
            break;
        }

        case NOKIA5110_SET_VOP:
        {
            //To be done later
            u8 Local_u8_Vop = Mod_str_Nokia5110Configurations.Vop;

            *Copy_pu8_CommandFrame = Local_u8_Vop;
            
            *Copy_pu8_CommandFrame |= (1 << NOKIA5110_B7);

            Local_u8_ErrorFlag = ES_OK;
            break;
        }

        default:
        {
            //If a non correct command is sent 0x00 Frame is sent
            Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
            break;
        }
    }

    return Local_u8_ErrorFlag;
}

/**
 * @brief Converts given y - coordinate into the bank number (Y-address)
 * 
 * @param Copy_pu8_Y y-coordinate
 * @return ErrorState_t 
 */
static ErrorState_t enu_ConvertCoordinatesToAddresses(u8* Copy_pu8_Y)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_pu8_Y)
    {   if(*Copy_pu8_Y > 47 || *Copy_pu8_Y < 0)
        {
            Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
        }
        else
        {
            *Copy_pu8_Y /= 8 ;  //Since each bank contains 8 rows, therefore integer division results in the number of bank

            Local_u8_ErrorFlag = ES_OK; 
        }
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }


    return Local_u8_ErrorFlag;
}

/**
 * @brief  Draws a pixel with given colour on the LCD matrix and LCD buffer
 * 
 * @param Copy_u8_Y  y coordinate
 * @param Copy_u8_X  x coordinate
 * @param Copy_u8_Colour Colour (white or black)
 * @return ErrorState_t 
 */
static ErrorState_t enu_DrawPixel(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour)
{
    u8 Local_u8_ErrorFlag = ES_NOK, Local_u8_DataFrame = 0, Local_u8_BitNumber = 0, Local_u8_CommandFrame = 0;

    if((Copy_u8_X > NOKIA5110_X_MAX || Copy_u8_X < NOKIA5110_X_MIN) || (Copy_u8_Y > 47 || Copy_u8_Y < NOKIA5110_Y_MIN) || (Copy_u8_Colour != NOKIA5110_WHITE_COLOUR && Copy_u8_Colour != NOKIA5110_BLACK_COLOUR))
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }
    else
    {   
        //Acquires Bit Number before y-coordinate is converted
        Local_u8_BitNumber = (Copy_u8_Y % 8);

        //Converts coordnates into addresses
        enu_ConvertCoordinatesToAddresses(&Copy_u8_Y); //Only y-coordinate needs conversion

        //Gets needed Element from buffer [Y-Address, X-Address]
        Local_u8_DataFrame =  LOC_au8_BufferArray[Copy_u8_Y][Copy_u8_X];

        //Masking the intended bit
        Local_u8_DataFrame &= ~(1 << Local_u8_BitNumber);

        //Placing needed colour in the frame
        Local_u8_DataFrame |= (Copy_u8_Colour << Local_u8_BitNumber);

        //Updating LCD Buffer
        LOC_au8_BufferArray[Copy_u8_Y][Copy_u8_X] = Local_u8_DataFrame;
        
        //Modifying Y and X addresses in the LCD object
        Mod_str_Nokia5110Configurations.Y_Address = Copy_u8_Y;
        Mod_str_Nokia5110Configurations.X_Address = Copy_u8_X;

        //Setting the X and Y addresses for the LCD
        enu_SendCommand(NOKIA5110_SET_Y_ADDRESS);
        enu_SendCommand(NOKIA5110_SET_X_ADDRESS);

        //Sending Data frame to LCD
        enu_SendData(Local_u8_DataFrame);

        //Sends Data Frame to LCD
        Local_u8_ErrorFlag = ES_OK;
    }

    return Local_u8_ErrorFlag; 
}

/**
 * @brief Clears RAM and LCD buffer
 * 
 * @return ErrorState_t 
 */
static ErrorState_t enu_ClearRAM()
{
    u8 Local_ErrorFlag = ES_NOK;

    //Setting Address Counter (AC) at (0,0)
    Mod_str_Nokia5110Configurations.Y_Address = 0;
    Mod_str_Nokia5110Configurations.X_Address = 0;

    enu_SendCommand(NOKIA5110_SET_Y_ADDRESS);
    enu_SendCommand(NOKIA5110_SET_X_ADDRESS);

    for(u8 i = 0; i <= 5; i++)
    {
        for(u8 j = 0; j <= 83; j++)
        {
            LOC_au8_BufferArray[i][j] = 0x00; //Clearing Buffer element

            enu_SendData(0x00); //Clearing RAM
        }
    }

    return Local_ErrorFlag;
}

/**
 * @brief Draws a filled rectangle at the specified area
 * 
 * @param Copy_u8_Y y-coordinate of the top left corner
 * @param Copy_u8_X y-coordinate of the top left corner
 * @param Copy_u8_Length rectangle's length (in the direction of the x - axis)
 * @param Copy_u8_Width rectangle's width (in the direction of the y - axis)
 * @return ErrorState_t 
 */
static ErrorState_t enu_DrawFillRectangle(u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Length, u8 Copy_u8_Width, u8 Copy_u8_Colour)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    u8 Local_u8_X = 0, Local_u8_Y = 0; //Addresses
    u8 i = 0, j = 0; // Loop Counters

    u8 Local_u8_CoordiantesValidation = False; //Validation boolean
    u8 Local_u8_ColourValidation = False; //Validation boolean
    u8 Local_u8_LengthAndWidthValidation = False; //Validation boolean
    u8 Local_u8_YWrapAroundCondition = False; //Wrap around condition for Y
    u8 Local_u8_XWrapAroundCondition = False; //Wrap around condition for X

    Local_u8_CoordiantesValidation = (Copy_u8_X >= NOKIA5110_X_COORDINATE_MIN && Copy_u8_X <= NOKIA5110_X_COORDINATE_MAX) && (Copy_u8_Y >= NOKIA5110_Y_COORDINATE_MIN && Copy_u8_Y <= NOKIA5110_Y_COORDINATE_MAX);
    Local_u8_ColourValidation = (Copy_u8_Colour == NOKIA5110_BLACK_COLOUR) || (Copy_u8_Colour == NOKIA5110_WHITE_COLOUR);
    Local_u8_LengthAndWidthValidation = (Copy_u8_Length <= NOKIA5110_LCD_LENGTH) && (Copy_u8_Width <= NOKIA5110_LCD_WIDTH); 
    Local_u8_XWrapAroundCondition = Copy_u8_Y + Copy_u8_Width > NOKIA5110_Y_COORDINATE_MAX;
    Local_u8_XWrapAroundCondition = Copy_u8_X + Copy_u8_Length > NOKIA5110_X_COORDINATE_MAX;

    if(Local_u8_CoordiantesValidation && Local_u8_ColourValidation && Local_u8_LengthAndWidthValidation)
    {
        //Converting starting coordiantes into addresses
        enu_ConvertCoordinatesToAddresses(&Local_u8_Y);   
        Local_u8_X = Copy_u8_X;

        //Adjusting LCD obkect configurations
        Mod_str_Nokia5110Configurations.Y_Address = Local_u8_Y;
        Mod_str_Nokia5110Configurations.X_Address = Local_u8_X;

        //Setting address counter to the addrresses of the starting point
        enu_SendCommand(NOKIA5110_SET_Y_ADDRESS);
        enu_SendCommand(NOKIA5110_SET_X_ADDRESS);

        //Drawing rectangle
        for (i = Copy_u8_X; i < Copy_u8_X + Copy_u8_Length; i++)
        {
            for(j = Copy_u8_Y; j < Copy_u8_Y + Copy_u8_Width; j++)
            {
                enu_DrawPixel(j, i, Copy_u8_Colour);
            }
        }         

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }

    return Local_u8_ErrorFlag;
}

/**
 * @brief Draws an ASCII character
 * 
 * @param Copy_u8_ASCII ASCII code
 * @param Copy_u8_Y y-coordinate of the ' ' left corner
 * @param Copy_u8_X y-coordinate of the ' ' left corner
 * @param Copy_u8_Colour Colour
 * @return ErrorState_t 
 */
static ErrorState_t enu_DrawASCII(u8 Copy_u8_ASCII, u8 Copy_u8_Y, u8 Copy_u8_X, u8 Copy_u8_Colour)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    u8 Local_u8_Line  = 0;

    if(1)
    {   
        //Erasing a 5 x 8 filled rectangle to draw the character on  
        enu_DrawFillRectangle(Copy_u8_Y, Copy_u8_X, 5, 8, NOKIA5110_WHITE_COLOUR);

        //Drawing the 5 x 7 Character
        for (u8 i = 0; i < 5; i++) 
        { 
            //Getting the needed bits for the column i 
            u8 Local_u8_Line = LOC_u8_ASCII[Copy_u8_ASCII * 5 + i];

            //Drawwing each Pixel
            for (u8 j = 0; j < 8; j++, Local_u8_Line >>= 1)
            {
                if (Local_u8_Line & 1) //At the last bit Local_u8_Line is 0
                {
					enu_DrawPixel(Copy_u8_Y + j, Copy_u8_X + i, Copy_u8_Colour);
                } 
            }
        }

        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }
    else
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }

    return Local_u8_ErrorFlag;
}

/**
 * @brief Draws a line using Bresenham's Algorithm using only integer arithmetic for fast operation 
 * 
 * @param Copy_u8_Ystart starting y - coordinate
 * @param Copy_u8_Xstart starting x - coordinate
 * @param Copy_u8_Yend  ending y - coordinate
 * @param Copy_u8_Xend  ending x - coordinate
 * @return ErrorState_t 
 */
static ErrorState_t enu_DrawLine(u8 Copy_u8_Ystart, u8 Copy_u8_Xstart, u8 Copy_u8_Yend, u8 Copy_u8_Xend)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    u8 Local_u8_dx = 0; //delta x 
    u8 Local_u8_dy = 0; //delta y 
    u8 Local_u8_D = 0; //error 
    u8 Local_u8_x = 0, Local_u8_y = 0; //Graphing counters

    Local_u8_dx = Copy_u8_Xend - Copy_u8_Xstart;
    Local_u8_dy = Copy_u8_Yend - Copy_u8_Ystart;

    Local_u8_D = 2*Local_u8_dy - Local_u8_dx;
    Local_u8_y = Copy_u8_Ystart; //y sarts from y0 as do x starts from x0

    for(Local_u8_x = Copy_u8_Xstart; Local_u8_x <= Copy_u8_Xend; Local_u8_x++)
    {
        enu_DrawPixel(Local_u8_x, Local_u8_y, NOKIA5110_BLACK_COLOUR);

        if(Local_u8_D > 0)
        {
            Local_u8_dy++; //The most accurate point lies in the positive plane therefore y should e incremented

            Local_u8_D -= 2*Local_u8_dy; //The most accurate point lies in the positive plane, therefore y should e incremented

        }
        else
        {
            Local_u8_D +=  2*Local_u8_dy; //The most accurate point lies in the negative plane, therefore y will remain the same
        }
    }

    return Local_u8_ErrorFlag; 
}