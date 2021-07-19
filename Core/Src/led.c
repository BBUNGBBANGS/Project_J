#include "led.h"

uint8 LED_Control_time;
void LED_Control(void)
{
    LED_Control_time++;
    if(LED_Control_time>100)
    {
        LED_Control_time = 0;
    }

    if(LED_Control_time<=25)
    {
        HAL_GPIO_WritePin(LED_1_GROUP,LED_1_PIN,LED_ON);
        HAL_GPIO_WritePin(LED_2_GROUP,LED_2_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_3_GROUP,LED_3_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_4_GROUP,LED_4_PIN,LED_OFF);
    }
    else if((25<LED_Control_time)&&(LED_Control_time<=50))
    {
        HAL_GPIO_WritePin(LED_1_GROUP,LED_1_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_2_GROUP,LED_2_PIN,LED_ON);
        HAL_GPIO_WritePin(LED_3_GROUP,LED_3_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_4_GROUP,LED_4_PIN,LED_OFF);
    }
    else if((50<LED_Control_time)&&(LED_Control_time<=75))
    {
        HAL_GPIO_WritePin(LED_1_GROUP,LED_1_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_2_GROUP,LED_2_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_3_GROUP,LED_3_PIN,LED_ON);
        HAL_GPIO_WritePin(LED_4_GROUP,LED_4_PIN,LED_OFF);
    }
    else
    {
        HAL_GPIO_WritePin(LED_1_GROUP,LED_1_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_2_GROUP,LED_2_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_3_GROUP,LED_3_PIN,LED_OFF);
        HAL_GPIO_WritePin(LED_4_GROUP,LED_4_PIN,LED_ON);
    }

}