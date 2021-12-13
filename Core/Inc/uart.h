#include "main.h"
#include <string.h>
#include <stdio.h>

#define UART1                   huart1

#define MENU_USERINFO           (0)
#define MENU_MAIN               (1)
#define MENU_WATCH              (2)
#define MENU_THERMOMETER        (3)
#define MENU_GAME               (4)
#define MENU_ERROR              (5)

#define MAIN_USERINFO_ASCII             ('0')
#define MAIN_WATCH_ASCII                ('1')
#define MAIN_THERMOMETER_ASCII          ('2')
#define MAIN_GAME_ASCII                 ('3')

#define WATCH_USERINFO_ASCII            ('0')
#define WATCH_START_ASCII               ('1')
#define WATCH_RESET_ASCII               ('2')
#define WATCH_STOP_ASCII                ('3')
#define WATCH_DISPLAY_CURRENT_ASCII     ('8')
#define WATCH_GOTO_MAIN_ASCII           ('9')

#define THERMO_USERINFO_ASCII           ('0')
#define THERMO_CELSIUS_ASCII            ('1')
#define THERMO_FAHRENHEIT_ASCII         ('2')
#define THERMO_DISPLAY_CURRENT_ASCII    ('8')
#define THERMO_GOTO_MAIN_ASCII          ('9')

#define GAME_USERINFO_ASCII             ('0')
#define GAME_START_ASCII                ('1')
#define GAME_DISPLAY_CURRENT_ASCII      ('8')
#define GAME_GOTO_MAIN_ASCII            ('9')

#define PRINT_OUT_LOCK_OFF  (0)
#define PRINT_OUT_LOCK_ON   (1)

extern void Uart_Receive_Init(void);
extern void Uart_Transmit(void);