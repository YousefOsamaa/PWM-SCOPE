#ifndef SPI_PRIVATE_FILE
#define SPI_PRIVATE_FILE



//SPI Control Register – SPCR
#define SPCR  (*(volatile u8*)0x2D)
typedef enum
{

    SPCR_SPR0 , //Bit 0 – SPR0 : SPI Clock Rate Select 0
    SPCR_SPR1 , //Bit 1 - SPR1 : SPI Clock Rate Select 1 
    SPCR_CPHA , //Bit 2 – CPHA: Clock Phase
    SPCR_CPOL , //Bit 3 – CPOL: Clock Polarity
    SPCR_MSTR , //Bit 4 – MSTR: Master/Slave Select  
    SPCR_DORD , //Bit 5 – DORD: Data Order
    SPCR_SPE ,  //Bit 6 – SPE: SPI Enable
    SPCR_SPIE , //Bit 7 – SPIE: SPI Interrupt Enable

}SPCR_t;

//SPI Status Register – SPSR
#define SPSR  (*(volatile u8*)0x2E)
typedef enum
{

    SPSR_SPI2X, // Bit 0 – SPI2X: Double SPI Speed Bit
    SPSR_RESERVED0 ,   
    SPSR_RESERVED1 , 
    SPSR_RESERVED2 , 
    SPSR_RESERVED3 ,    
    SPSR_RESERVED4 ,  
    SPSR_WCOL,  //Bit 6 – WCOL: Write COLlision Flag
    SPSR_SPIF , //Bit 7 – SPIF: SPI Interrupt Flag

}SPSR_t;

//SPI Data Register – SPDR
#define SPDR  (*(volatile u8*)0x2F)
typedef enum
{

    SPDR_B0   ,//SPI Data Register Bit 0
    SPDR_B1   ,//SPI Data Register Bit 1   
    SPDR_B2   ,//SPI Data Register Bit 2 
    SPDR_B3   ,//SPI Data Register Bit 3 
    SPDR_B4   ,//SPI Data Register Bit 4    
    SPDR_B5   ,//SPI Data Register Bit 5  
    SPDR_B6   ,//SPI Data Register Bit 6
    SPDR_B7   ,//SPI Data Register Bit 7

}SPDR_t;


//Master and Slave Mode
#define SPI_SLAVE_MODE         (0)
#define SPI_MASTER_MODE        (1)

//Interrupt Mode
#define SPI_ACTIVATE_POLLING_MODE     (0)
#define SPI_ACTIVATE_INTERRUPT_MODE   (1)

//Clock Polartiry 
#define SPI_CPOL_LOW_IDLE        (0)
#define SPI_CPOL_HIGH_IDLE       (1)

//Clock Phase 
#define SPI_CPHA_SAMPLE_LEADING        (0)
#define SPI_CPHA_SAMPLE_LAGGING        (1)


//Data Order
#define SPI_DORD_MSB_FIRST    (0)
#define SPI_DORD_LSB_FIRST    (1)

//Double Speed SPI
#define SPI_DEACTIVATE_DOUPLE_SPEED_MODE    (0)
#define SPI_ACTIVATE_DOUPLE_SPEED_MODE      (1)

//Master Clock Selection
#define SPI_PS_4         (0)
#define SPI_PS_16        (1)
#define SPI_PS_64        (2)
#define SPI_PS_128       (3)


//SPI Communication State
#define SPI_FREE      (0)
#define SPI_BUSY      (1)


//SPI ISR Status
#define SPI_EXTERNAL_ISR   (0)
#define SPI_INTERNAL_ISR   (1)


#endif
