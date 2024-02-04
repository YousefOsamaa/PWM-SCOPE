#ifndef SPI_INTERFACE_FILE
#define SPI_INTERFACE_FILE

#include "../../LIB/ErrorStates.h"
#include "../../LIB/STD.h"


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

//SPI Communication State
#define SPI_FREE      (0)
#define SPI_BUSY      (1)


extern ErrorState_t SPI_enu_Initialization (void);

extern ErrorState_t SPI_enu_StartTranReceive (u8* Copy_u8_TranReceivedData);

extern ErrorState_t SPI_enu_MasterSend(u8 Copy_u8_Data);

extern ErrorState_t SPI_enu_SlaveReceive(u8* Copy_pu8_Data);

extern ErrorState_t SPI_enu_SetCommStateBusy(void);

extern ErrorState_t SPI_enu_GetCommState(u8* Copy_pu8_State);

extern ErrorState_t SPI_enu_SetCallBack(void (*Copy_pfun_AppFunction)(void*), void* Copy_pvid_Parameters);

extern ErrorState_t SPI_enu_SetDataOrderMode(u8 Copy_u8_DataOrderMode);


#endif
