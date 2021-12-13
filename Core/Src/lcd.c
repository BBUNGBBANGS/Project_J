#include "lcd.h"
static void LCD_Power_Control(uint8 status, uint8 duty);
static void LCD_Output_Red(uint8 data);
static void LCD_Output_Green(uint8 data);
static void LCD_Output_Blue(uint8 data);

void LCD_Init(void)
{
    LCD_Power_Control(LCD_POWER_ON,100);
}

static void LCD_Power_Control(uint8 status, uint8 duty)
{
    HAL_GPIO_WritePin(LCD_POWER_MODULE,LCD_POWER_PIN,status);

    return;
}

void LCD_Set_Clock(void)
{
    static uint8 state;
    static uint8 counter;
    state = (~state)&0x01;

    if(counter<16)
    {
        HAL_GPIO_WritePin(LCD_DE_MODULE,LCD_DE_PIN,LCD_DE_ON);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_DE_MODULE,LCD_DE_PIN,LCD_DE_OFF);
        if(counter == 17)
        {
            HAL_GPIO_WritePin(LCD_HSYNC_MODULE,LCD_HSYNC_PIN,LCD_HSYNC_OFF);
        }
        if(counter == 18)
        {
            HAL_GPIO_WritePin(LCD_HSYNC_MODULE,LCD_HSYNC_PIN,LCD_HSYNC_ON);
        }
        if(counter == 19)
        {
            counter = 0;
        }
    }
    counter++;

    HAL_GPIO_WritePin(LCD_CLK_MODULE,LCD_CLK_PIN,state);
    return;
}

void LCD_Set_Color(void)
{
    LCD_Output_Red(255);
    LCD_Output_Green(255);
    LCD_Output_Blue(255);

    return;
}

static void LCD_Output_Red(uint8 data)
{
    HAL_GPIO_WritePin(LCD_R0_MODULE,LCD_R0_PIN,((data)&0x01));
    HAL_GPIO_WritePin(LCD_R1_MODULE,LCD_R1_PIN,((data>>1)&0x01));
    HAL_GPIO_WritePin(LCD_R2_MODULE,LCD_R2_PIN,((data>>2)&0x01));
    HAL_GPIO_WritePin(LCD_R3_MODULE,LCD_R3_PIN,((data>>3)&0x01));
    HAL_GPIO_WritePin(LCD_R4_MODULE,LCD_R4_PIN,((data>>4)&0x01));
    HAL_GPIO_WritePin(LCD_R5_MODULE,LCD_R5_PIN,((data>>5)&0x01));
    HAL_GPIO_WritePin(LCD_R6_MODULE,LCD_R6_PIN,((data>>6)&0x01));
    HAL_GPIO_WritePin(LCD_R7_MODULE,LCD_R7_PIN,((data>>7)&0x01));
    return;
}

static void LCD_Output_Green(uint8 data)
{
    HAL_GPIO_WritePin(LCD_G0_MODULE,LCD_G0_PIN,((data)&0x01));
    HAL_GPIO_WritePin(LCD_G1_MODULE,LCD_G1_PIN,((data>>1)&0x01));
    HAL_GPIO_WritePin(LCD_G2_MODULE,LCD_G2_PIN,((data>>2)&0x01));
    HAL_GPIO_WritePin(LCD_G3_MODULE,LCD_G3_PIN,((data>>3)&0x01));
    HAL_GPIO_WritePin(LCD_G4_MODULE,LCD_G4_PIN,((data>>4)&0x01));
    HAL_GPIO_WritePin(LCD_G5_MODULE,LCD_G5_PIN,((data>>5)&0x01));
    HAL_GPIO_WritePin(LCD_G6_MODULE,LCD_G6_PIN,((data>>6)&0x01));
    HAL_GPIO_WritePin(LCD_G7_MODULE,LCD_G7_PIN,((data>>7)&0x01));
    return;
}

static void LCD_Output_Blue(uint8 data)
{
    HAL_GPIO_WritePin(LCD_B0_MODULE,LCD_B0_PIN,((data)&0x01));
    HAL_GPIO_WritePin(LCD_B1_MODULE,LCD_B1_PIN,((data>>1)&0x01));
    HAL_GPIO_WritePin(LCD_B2_MODULE,LCD_B2_PIN,((data>>2)&0x01));
    HAL_GPIO_WritePin(LCD_B3_MODULE,LCD_B3_PIN,((data>>3)&0x01));
    HAL_GPIO_WritePin(LCD_B4_MODULE,LCD_B4_PIN,((data>>4)&0x01));
    HAL_GPIO_WritePin(LCD_B5_MODULE,LCD_B5_PIN,((data>>5)&0x01));
    HAL_GPIO_WritePin(LCD_B6_MODULE,LCD_B6_PIN,((data>>6)&0x01));
    HAL_GPIO_WritePin(LCD_B7_MODULE,LCD_B7_PIN,((data>>7)&0x01));
    return;
}