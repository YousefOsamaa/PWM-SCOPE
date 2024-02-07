/**
 * @file PWMScope_Private.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PWMSCOPE_PRIVATE_H_
#define PWMSCOPE_PRIVATE_H_

/**
 * @brief All Physical properties concerning X - axis 
 * 
 */
#define PWMSCOPE_BORDER_VERTICAL_SHIFT   (17)
#define PWMSCOPE_BORDER_HORIZOTAL_SHIFT  (0)
#define PWMSCOPE_BORDER_THICKNESS        (1)
#define PWMSCOPE_BORDER_LENGTH           (NOKIA5110_LCD_LENGTH)
#define PWMSCOPE_BORDER_COLOUR           (NOKIA5110_WHITE_COLOUR)

/**
 * @brief All Physical properties concerning X - axis 
 * 
 */
#define PWMSCOPE_X_AXIS_VERTICAL_SHIFT   (47)
#define PWMSCOPE_X_AXIS_HORIZOTAL_SHIFT  (0)
#define PWMSCOPE_X_AXIS_THICKNESS        (1)
#define PWMSCOPE_X_AXIS_LENGTH           (NOKIA5110_LCD_LENGTH)
#define PWMSCOPE_X_AXIS_COLOUR           (NOKIA5110_BLACK_COLOUR)
#define PWMSCOPE_X_AXIS_SCALE             1


/**
 * @brief All Physical properties concerning y - axis 
 * 
 */
#define PWMSCOPE_Y_AXIS_VERTICAL_SHIFT   (20)
#define PWMSCOPE_Y_AXIS_HORIZOTAL_SHIFT  (4)
#define PWMSCOPE_Y_AXIS_THICKNESS        (1)
#define PWMSCOPE_Y_AXIS_HEIGHT           (NOKIA5110_LCD_WIDTH - PWMSCOPE_Y_AXIS_VERTICAL_SHIFT)
#define PWMSCOPE_Y_AXIS_COLOUR           (NOKIA5110_BLACK_COLOUR)
#define PWMSCOPE_Y_AXIS_SCALE            (4)

#define PWMSCOPE_5V_VERTICAL_SHIFT  (PWMSCOPE_X_AXIS_VERTICAL_SHIFT - 5*PWMSCOPE_Y_AXIS_SCALE)

#define PWMSCOPE_T_LENGTH                 (40)

/**
 * @brief Contains the maximum number of signals that the scope buffer can handle, if overflowed the buffer will over write on the last wave only
 * 
 */
#define PWMSCOPE_MAX_DISPLAYED_SIGNALS 100

typedef struct 
{
    f32 Frequency;
    f32 DutyRatio;
    u32 CursorNumber;
    u32 OnSectionStartingPonit;
    u32 OnSectionEndingPoint;
    u32 OffSectionEndingPoint;

}PWM_t;

//Local Functions
static ErrorState_t enu_GenerateScopeScreen(void);

static ErrorState_t enu_DrawPWM(f32* Copy_af32_SignalsParameters);

/**
 * @brief To be done later
 */
// static ErrorState_t enu_GeneratePwmPattern(PWM_t Copy_str_Wave);

#endif /* PWMSCOPE_PRIVATE_H_ */