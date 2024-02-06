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
#define PWMSCOPE_X_AXIS_VERTICAL_SHIFT   (43)
#define PWMSCOPE_X_AXIS_HORIZOTAL_SHIFT  (0)
#define PWMSCOPE_X_AXIS_THICKNESS        (1)
#define PWMSCOPE_X_AXIS_LENGTH           (NOKIA5110_LCD_LENGTH)
#define PWMSCOPE_X_AXIS_COLOUR           (NOKIA5110_BLACK_COLOUR)


/**
 * @brief All Physical properties concerning y - axis 
 * 
 */
#define PWMSCOPE_Y_AXIS_VERTICAL_SHIFT   (22)
#define PWMSCOPE_Y_AXIS_HORIZOTAL_SHIFT  (4)
#define PWMSCOPE_Y_AXIS_THICKNESS        (1)
#define PWMSCOPE_Y_AXIS_HEIGHT           (NOKIA5110_LCD_WIDTH - PWMSCOPE_Y_AXIS_VERTICAL_SHIFT)
#define PWMSCOPE_Y_AXIS_COLOUR           (NOKIA5110_BLACK_COLOUR)


typedef struct 
{
    f32 Frequency;
    f32 DutyRatio;
}PWM_t;

//Local Functions
static ErrorState_t enu_GenerateScopeScreen(void);

#endif /* PWMSCOPE_PRIVATE_H_ */