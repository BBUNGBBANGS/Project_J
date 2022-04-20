#include "motor_driver.h"
//#include "as5048.h"

uint16 Motor_Driver_Duty = 30;
uint8 Motor_Driver_Step;
uint32 Motor_Angle_Offset;
uint8 Motor_Driver_Fault;
static void Motor_Driver_Output_Step(uint32 angle);
static void Motor_Driver_Output_Duty(uint16 duty);
static void Motor_Driver_Port_Set_Mode(uint16 pin,uint8 mode);
static void Motor_Drvier_Fault(void);
uint8 AS5048_Angle;
void Motor_Driver_Init(void)
{
    //HAL_GPIO_WritePin(MOTOR_DRIVER_ENABLE_MODULE,MOTOR_DRIVER_ENABLE_PIN,GPIO_PIN_SET);
}

void Motor_Drvier_Control(void)
{
    Motor_Driver_Output_Step(AS5048_Angle);
    Motor_Driver_Output_Duty(Motor_Driver_Duty);
    Motor_Drvier_Fault();
}

static void Motor_Driver_Output_Step(uint32 angle)
{
    uint8 step;
    uint32 Motor_Angle;

    step = 0;
    Motor_Angle = angle + Motor_Angle_Offset;

    if(Motor_Angle>36000)
    {
        Motor_Angle = 36000 - Motor_Angle;
    }

    if((0<=Motor_Angle)&&(Motor_Angle<6000))
    {
        step = MOTOR_STEP_1;
    }
    else if((6000<=Motor_Angle)&&(Motor_Angle<12000))
    {
        step = MOTOR_STEP_2;       
    }
    else if((12000<=Motor_Angle)&&(Motor_Angle<18000))
    {
        step = MOTOR_STEP_3;       
    }    
    else if((18000<=Motor_Angle)&&(Motor_Angle<24000))
    {
        step = MOTOR_STEP_4;       
    }    
    else if((24000<=Motor_Angle)&&(Motor_Angle<30000))
    {
        step = MOTOR_STEP_5;       
    }    
    else if((30000<=Motor_Angle)&&(Motor_Angle<36000))
    {
        step = MOTOR_STEP_6;       
    }
    else
    {
        /* error state */
    }

    Motor_Driver_Step = step;
}

static void Motor_Driver_Output_Duty(uint16 duty)
{
    uint8 step;

    step = Motor_Driver_Step;
    if(duty>0)
    {
        switch(step)
        {
            case MOTOR_STEP_1:
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_U,OUTPUT_TIM_MODE);
                MOTOR_DRIVER_TIMER_U->MOTOR_DRIVER_CHANNEL_U = duty;
                MOTOR_DRIVER_TIMER_V->MOTOR_DRIVER_CHANNEL_V = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_W->MOTOR_DRIVER_CHANNEL_W = MOTOR_DRIVER_OUTPUT_LOW;
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_V|LOWSIDE_PIN_W,OUTPUT_GPIO_MODE);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_V,GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_W,GPIO_PIN_RESET);
            break;
            case MOTOR_STEP_2:
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_U,OUTPUT_TIM_MODE);
                MOTOR_DRIVER_TIMER_U->MOTOR_DRIVER_CHANNEL_U = duty;       
                MOTOR_DRIVER_TIMER_V->MOTOR_DRIVER_CHANNEL_V = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_W->MOTOR_DRIVER_CHANNEL_W = MOTOR_DRIVER_OUTPUT_LOW;
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_V|LOWSIDE_PIN_W,OUTPUT_GPIO_MODE);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_V,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_W,GPIO_PIN_SET);
            break;       
            case MOTOR_STEP_3:
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_V,OUTPUT_TIM_MODE);
                MOTOR_DRIVER_TIMER_U->MOTOR_DRIVER_CHANNEL_U = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_V->MOTOR_DRIVER_CHANNEL_V = duty;
                MOTOR_DRIVER_TIMER_W->MOTOR_DRIVER_CHANNEL_W = MOTOR_DRIVER_OUTPUT_LOW;          
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_U|LOWSIDE_PIN_W,OUTPUT_GPIO_MODE);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_U,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_W,GPIO_PIN_SET);
            break;
            case MOTOR_STEP_4:           
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_V,OUTPUT_TIM_MODE);
                MOTOR_DRIVER_TIMER_U->MOTOR_DRIVER_CHANNEL_U = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_V->MOTOR_DRIVER_CHANNEL_V = duty;       
                MOTOR_DRIVER_TIMER_W->MOTOR_DRIVER_CHANNEL_W = MOTOR_DRIVER_OUTPUT_LOW;          
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_U|LOWSIDE_PIN_W,OUTPUT_GPIO_MODE);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_U,GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_W,GPIO_PIN_RESET);
            break;        
            case MOTOR_STEP_5:
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_W,OUTPUT_TIM_MODE);
                MOTOR_DRIVER_TIMER_U->MOTOR_DRIVER_CHANNEL_U = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_V->MOTOR_DRIVER_CHANNEL_V = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_W->MOTOR_DRIVER_CHANNEL_W = duty;            
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_U|LOWSIDE_PIN_V,OUTPUT_GPIO_MODE);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_U,GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_V,GPIO_PIN_RESET);       
            break;
            case MOTOR_STEP_6:          
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_W,OUTPUT_TIM_MODE);
                MOTOR_DRIVER_TIMER_U->MOTOR_DRIVER_CHANNEL_U = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_V->MOTOR_DRIVER_CHANNEL_V = MOTOR_DRIVER_OUTPUT_LOW;
                MOTOR_DRIVER_TIMER_W->MOTOR_DRIVER_CHANNEL_W = duty;            
                Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_U|LOWSIDE_PIN_V,OUTPUT_GPIO_MODE);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_U,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB,LOWSIDE_PIN_V,GPIO_PIN_SET);
            break;        
            default :
            break;
        }
    }
    else
    {
        Motor_Driver_Port_Set_Mode(LOWSIDE_PIN_U|LOWSIDE_PIN_V|LOWSIDE_PIN_W,OUTPUT_TIM_MODE);
        MOTOR_DRIVER_TIMER_U->MOTOR_DRIVER_CHANNEL_U = MOTOR_DRIVER_OUTPUT_LOW;
        MOTOR_DRIVER_TIMER_V->MOTOR_DRIVER_CHANNEL_V = MOTOR_DRIVER_OUTPUT_LOW;
        MOTOR_DRIVER_TIMER_W->MOTOR_DRIVER_CHANNEL_W = MOTOR_DRIVER_OUTPUT_LOW;     
    }
}

static void Motor_Driver_Port_Set_Mode(uint16 pin,uint8 mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    if(OUTPUT_TIM_MODE == mode)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    }
    else
    {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Alternate = 0;        
    }
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 
}

static void Motor_Drvier_Fault(void)
{
    Motor_Driver_Fault = HAL_GPIO_ReadPin(MOTOR_DRIVER_FAULT_MODULE,MOTOR_DRIVER_FAULT_PIN);
}
