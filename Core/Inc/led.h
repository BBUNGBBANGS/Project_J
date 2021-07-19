#include "main.h"

#define LED_1_GROUP         (GPIOB)
#define LED_2_GROUP         (GPIOB)
#define LED_3_GROUP         (GPIOH)
#define LED_4_GROUP         (GPIOI)

#define LED_1_PIN           (GPIO_PIN_6)
#define LED_2_PIN           (GPIO_PIN_7)
#define LED_3_PIN           (GPIO_PIN_4)
#define LED_4_PIN           (GPIO_PIN_8)

#define LED_ON              (GPIO_PIN_SET)
#define LED_OFF             (GPIO_PIN_RESET)

extern void LED_Control(void);