#ifndef ICU_PRIVATE
#define ICU_PRIVATE


#define ICU_CONTINOUS_MODE         (0)
#define ICU_SNGLE_CAPTURE_MODE     (1)


typedef enum
{
    ICU_IDLE,
    ICU_FIRST_RISING_EDGE,
    ICU_SECOND_RISING_EDGE,
    ICU_FALLING_EDGE,

}ICU_States;


//Local functions
void vid_CapturingFunction(void* Copy_pvid_FunctionParameters);

void vid_IncrementOverFlowCounter();




#endif