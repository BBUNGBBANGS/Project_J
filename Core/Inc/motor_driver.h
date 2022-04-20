#include "main.h"

#define MOTOR_STEP_1        (1)
#define MOTOR_STEP_2        (2)
#define MOTOR_STEP_3        (3)
#define MOTOR_STEP_4        (4)
#define MOTOR_STEP_5        (5)
#define MOTOR_STEP_6        (6)

#define MOTOR_DRIVER_TIMER_U            (TIM1)
#define MOTOR_DRIVER_TIMER_V            (TIM1)
#define MOTOR_DRIVER_TIMER_W            (TIM1)

#define MOTOR_DRIVER_CHANNEL_U          CCR1
#define MOTOR_DRIVER_CHANNEL_V          CCR2
#define MOTOR_DRIVER_CHANNEL_W          CCR3

#define MOTOR_DRIVER_FAULT_MODULE       (GPIOB)
#define MOTOR_DRIVER_FAULT_PIN          (GPIO_PIN_12)

#define MOTOR_DRIVER_ENABLE_MODULE      (GPIOA)
#define MOTOR_DRIVER_ENABLE_PIN         (GPIO_PIN_11)

#define MOTOR_DRIVER_OUTPUT_HIGH        (100)
#define MOTOR_DRIVER_OUTPUT_LOW         (0)

#define LOWSIDE_PIN_U                   (GPIO_PIN_13)
#define LOWSIDE_PIN_V                   (GPIO_PIN_14)
#define LOWSIDE_PIN_W                   (GPIO_PIN_15)

#define OUTPUT_TIM_MODE                 (1u)
#define OUTPUT_GPIO_MODE                (2u)


extern void Motor_Driver_Init(void);
extern void Motor_Drvier_Control(void);