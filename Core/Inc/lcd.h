#include "main.h"

#define LCD_SPI_MODULE          (hspi5)

#define LCD_R0_PIN              (GPIO_PIN_2)
#define LCD_R1_PIN              (GPIO_PIN_3)
#define LCD_R2_PIN              (GPIO_PIN_8)
#define LCD_R3_PIN              (GPIO_PIN_9)
#define LCD_R4_PIN              (GPIO_PIN_10)
#define LCD_R5_PIN              (GPIO_PIN_0)
#define LCD_R6_PIN              (GPIO_PIN_1)
#define LCD_R7_PIN              (GPIO_PIN_6)
#define LCD_R0_MODULE           (GPIOH)
#define LCD_R1_MODULE           (GPIOH) 
#define LCD_R2_MODULE           (GPIOH)
#define LCD_R3_MODULE           (GPIOH)
#define LCD_R4_MODULE           (GPIOH)
#define LCD_R5_MODULE           (GPIOC) 
#define LCD_R6_MODULE           (GPIOB) 
#define LCD_R7_MODULE           (GPIOG)

#define LCD_G0_PIN              (GPIO_PIN_5)
#define LCD_G1_PIN              (GPIO_PIN_6)
#define LCD_G2_PIN              (GPIO_PIN_13)
#define LCD_G3_PIN              (GPIO_PIN_10)
#define LCD_G4_PIN              (GPIO_PIN_15)
#define LCD_G5_PIN              (GPIO_PIN_0)
#define LCD_G6_PIN              (GPIO_PIN_1)
#define LCD_G7_PIN              (GPIO_PIN_2)
#define LCD_G0_MODULE           (GPIOE)
#define LCD_G1_MODULE           (GPIOE)
#define LCD_G2_MODULE           (GPIOH)
#define LCD_G3_MODULE           (GPIOG)
#define LCD_G4_MODULE           (GPIOH)
#define LCD_G5_MODULE           (GPIOI)
#define LCD_G6_MODULE           (GPIOI)
#define LCD_G7_MODULE           (GPIOI)

#define LCD_B0_PIN              (GPIO_PIN_4)
#define LCD_B1_PIN              (GPIO_PIN_12)
#define LCD_B2_PIN              (GPIO_PIN_6)
#define LCD_B3_PIN              (GPIO_PIN_11)
#define LCD_B4_PIN              (GPIO_PIN_4)
#define LCD_B5_PIN              (GPIO_PIN_5)
#define LCD_B6_PIN              (GPIO_PIN_6)
#define LCD_B7_PIN              (GPIO_PIN_7)
#define LCD_B0_MODULE           (GPIOE)
#define LCD_B1_MODULE           (GPIOG)
#define LCD_B2_MODULE           (GPIOD)
#define LCD_B3_MODULE           (GPIOG)
#define LCD_B4_MODULE           (GPIOI)
#define LCD_B5_MODULE           (GPIOI)
#define LCD_B6_MODULE           (GPIOI)
#define LCD_B7_MODULE           (GPIOI)

#define LCD_POWER_PIN           (GPIO_PIN_8)
#define LCD_POWER_MODULE        (GPIOI)
#define LCD_POWER_OFF           (0)
#define LCD_POWER_ON            (1)

#define LCD_CLK_PIN             (GPIO_PIN_7)
#define LCD_CLK_MODULE          (GPIOG)

#define LCD_DE_PIN              (GPIO_PIN_10)
#define LCD_DE_MODULE           (GPIOF)
#define LCD_DE_OFF              (0)
#define LCD_DE_ON               (1)

#define LCD_HSYNC_PIN           (GPIO_PIN_10)
#define LCD_HSYNC_MODULE        (GPIOI)
#define LCD_HSYNC_OFF           (0)
#define LCD_HSYNC_ON            (1)

extern void LCD_Init(void);
extern void LCD_Set_Color(void);
extern void LCD_Set_Clock(void);