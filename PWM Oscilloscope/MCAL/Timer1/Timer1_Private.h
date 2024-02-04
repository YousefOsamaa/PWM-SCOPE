#ifndef TIMER1_PRIVATE
#define TIMER1_PRIVATE


//Timer/Counter 1 Control Register A 
#define TCCR1A *(volatile u8*)0x4F
typedef enum
{

 TCCR1A_WGM10 ,    
 TCCR1A_WGM11 ,  
 TCCR1A_FOC1B  ,      
 TCCR1A_FOC1A  ,      
 TCCR1A_COM1B0  ,  
 TCCR1A_COM1B1  ,    
 TCCR1A_COM1A0  ,  
 TCCR1A_COM1A1  ,    

}TCCR1A_t;

#define TCCR1B *(volatile u8*)0x4E
typedef enum
{

    
 TCCR1B_CS10  ,      //Bit 0 – CS10 Clock Select
 TCCR1B_CS11  ,      //Bit 1 – CS11: Clock Select
 TCCR1B_CS12  ,     //Bit 2 – CS12: Clock Select
 TCCR1B_WGM12 ,     //Bit 3 – WGM12: Waveform Generation Mode
 TCCR1B_WGM13 ,      //Bit 4 – WGM13: Waveform Generation Mode
 TCCR1B_RESERVED  ,  //Bit 5 – Reserved Bit
 TCCR1B_ICES1  ,    //Bit 6 – ICES1: Input Capture Edge Select
 TCCR1B_ICNC1  ,    //Bit 7 – ICNC1: Input Capture Noise Canceler


}TCCR1B_t;

#define TCNT1H *(volatile u8*)0x4D
typedef enum
{

 TCNT1H_B8 ,    //Timer/Counter 1 register Bit 8  
 TCNT1H_B9 ,    //Timer/Counter 1 register Bit 9 
 TCNT1H_B10,    //Timer/Counter 1 register Bit 10  
 TCNT1H_B11,    //Timer/Counter 1 register Bit 11 
 TCNT1H_B12,    //Timer/Counter 1 register Bit 12  
 TCNT1H_B13,    //Timer/Counter 1 register Bit 13  
 TCNT1H_B14,    //Timer/Counter 1 register Bit 14  
 TCNT1H_B15     //Timer/Counter 1 register Bit 15     

}TCNT1H_t;

#define TCNT1L *(volatile u8*)0x4C
typedef enum
{

 TCNT1L_B0,    //Timer/Counter 1 register Bit 0  
 TCNT1L_B1,    //Timer/Counter 1 register Bit 1 
 TCNT1L_B2,    //Timer/Counter 1 register Bit 2  
 TCNT1L_B3,    //Timer/Counter 1 register Bit 3  
 TCNT1L_B4,    //Timer/Counter 1 register Bit 4  
 TCNT1L_B5,    //Timer/Counter 1 register Bit 5  
 TCNT1L_B6,    //Timer/Counter 1 register Bit 6  
 TCNT1L_B7     //Timer/Counter 1 register Bit 7      

}TCNT1L_t;

#define OCR1AH *(volatile u8*)0x4B
typedef enum
{

 OCR1AH_B8 ,    //Output Compare Register 1 A register Bit 8  
 OCR1AH_B9 ,    //Output Compare Register 1 A register Bit 9 
 OCR1AH_B10,    //Output Compare Register 1 A register Bit 10  
 OCR1AH_B11,    //Output Compare Register 1 A register Bit 11 
 OCR1AH_B12,    //Output Compare Register 1 A register Bit 12  
 OCR1AH_B13,    //Output Compare Register 1 A register Bit 13  
 OCR1AH_B14,    //Output Compare Register 1 A register Bit 14  
 OCR1AH_B15     //Output Compare Register 1 A register Bit 15     

}OCR1AH_t;

#define OCR1AL *(volatile u8*)0x4A
typedef enum
{

 OCR1AL_B0,    //Output Compare Register 1 A register Bit 0  
 OCR1AL_B1,    //Output Compare Register 1 A register Bit 1 
 OCR1AL_B2,    //Output Compare Register 1 A register Bit 2  
 OCR1AL_B3,    //Output Compare Register 1 A register Bit 3  
 OCR1AL_B4,    //Output Compare Register 1 A register Bit 4  
 OCR1AL_B5,    //Output Compare Register 1 A register Bit 5  
 OCR1AL_B6,    //Output Compare Register 1 A register Bit 6  
 OCR1AL_B7     //Output Compare Register 1 A register Bit 7      

}OCR1AL_t;

#define OCR1BH *(volatile u8*)0x49
typedef enum
{

 OCR1BH_B8 ,    //Output Compare Register 1 B register Bit 8  
 OCR1BH_B9 ,    //Output Compare Register 1 B register Bit 9 
 OCR1BH_B10,    //Output Compare Register 1 B register Bit 10  
 OCR1BH_B11,    //Output Compare Register 1 B register Bit 11 
 OCR1BH_B12,    //Output Compare Register 1 B register Bit 12  
 OCR1BH_B13,    //Output Compare Register 1 B register Bit 13  
 OCR1BH_B14,    //Output Compare Register 1 B register Bit 14  
 OCR1BH_B15     //Output Compare Register 1 B register Bit 15     

}OCR1BH_t;

#define OCR1BL *(volatile u8*)0x48
typedef enum
{

 OCR1BL_B0,    //Output Compare Register 1 B register Bit 0  
 OCR1BL_B1,    //Output Compare Register 1 B register Bit 1 
 OCR1BL_B2,    //Output Compare Register 1 B register Bit 2  
 OCR1BL_B3,    //Output Compare Register 1 B register Bit 3  
 OCR1BL_B4,    //Output Compare Register 1 B register Bit 4  
 OCR1BL_B5,    //Output Compare Register 1 B register Bit 5  
 OCR1BL_B6,    //Output Compare Register 1 B register Bit 6  
 OCR1BL_B7     //Output Compare Register 1 B register Bit 7      

}OCR1BL_t;

#define ICR1H *(volatile u8*)0x47
typedef enum
{

 ICR1H_B8 ,    //Input Capture Register 1  register Bit 8  
 ICR1H_B9 ,    //Input Capture Register 1  register Bit 9 
 ICR1H_B10,    //Input Capture Register 1  register Bit 10  
 ICR1H_B11,    //Input Capture Register 1  register Bit 11 
 ICR1H_B12,    //Input Capture Register 1  register Bit 12  
 ICR1H_B13,    //Input Capture Register 1  register Bit 13  
 ICR1H_B14,    //Input Capture Register 1  register Bit 14  
 ICR1H_B15     //Input Capture Register 1  register Bit 15     

}ICR1H_t;

#define ICR1L *(volatile u8*)0x46
typedef enum
{

 ICR1L_B0,    //Input Capture Register 1  register Bit 0  
 ICR1L_B1,    //Input Capture Register 1  register Bit 1 
 ICR1L_B2,    //Input Capture Register 1  register Bit 2  
 ICR1L_B3,    //Input Capture Register 1  register Bit 3  
 ICR1L_B4,    //Input Capture Register 1  register Bit 4  
 ICR1L_B5,    //Input Capture Register 1  register Bit 5  
 ICR1L_B6,    //Input Capture Register 1  register Bit 6  
 ICR1L_B7     //Input Capture Register 1  register Bit 7      

}ICR1L_t;

//Timer/Counter  Interrurpt Mask Register (TIMSK) FOR TIMER0, 1, AND 2 
#define TIMSK *(volatile u8*)0x59
typedef enum
{

 TIMSK_TOIE0  ,  //Timer/Counter 0 Overflow Interrupt Enable
 TIMSK_OCIE0  ,  //Timer/Counter 0 Output Compare Match Interrupt Enable
 TIMSK_TOIE1  ,  
 TIMSK_OCIE1B ,  
 TIMSK_OCIE1A ,  
 TIMSK_TICIE1  ,  
 TIMSK_TOIE2  ,   //Timer/Counter 2 Overflow Interrupt Enable
 TIMSK_OCIE2  ,   //Timer/Counter 0 Output Compare Match Interrupt Enable

}TIMSK_t;

//Timer/Counter  Interrupt Flag Register (TIFR)
#define TIFR  *(volatile u8*)0x58
typedef enum
{

 TIFR_TOV1   =   2 , //Timer/Counter 1 Overflow Flag 
 TIFR_OCF1B  =   3 , //Output Compare Flag B FOR Timer/Counter 1
 TIFR_OCF1A  =   4 , //Output Compare Flag A FOR Timer/Counter 1
 TIFR_ICF1  =   5 , //Input Capture Interrupt Enable

}TIFR_t;



//Clock Selection Options
#define TIMER1_V_GND             0
#define TIMER1_PS_1              1
#define TIMER1_PS_8              2   
#define TIMER1_PS_64             3
#define TIMER1_PS_256            4
#define TIMER1_PS_1024           5
#define TIMER1_PS_FALLING_EGDE      6   
#define TIMER1_PS_RISING_EGDE       7   


//Timer Modes
#define TIMER1_NORMAL           0
#define TIMER1_CTC              1


//Interrupt Modes 
#define TIMER1_ACTIVATE_INT_MODE                         1
#define TIMER1_ACTIVATE_POLLING_MODE                     0

//Input Capture Edge Mode 
#define TIMER1_ICU_RISING_EDGE                       1
#define TIMER1_ICU_FALLING_EDGE                      0

//Input Capture Interrupt Mode 
#define TIMER1_ACTIVATE_ICU_INTERRUPT                       1
#define TIMER1_DEACTIVATE_ICU_INTERRUPT                     0

//ISRs Count
#define TIMER1_ISR_COUNT   4

//ISR Pointers Location
#define TIMER1_CAPTURE_EVENT_ISR       0
#define TIMER1_CTC_A_ISR               1
#define TIMER1_CTC_B_ISR               2
#define TIMER1_OVERFLOW_ISR            3

//Noise Canceler
#define TIMER1_ACTIVATE_NC             1
#define TIMER1_DEACTIVATE_NC           0

#endif