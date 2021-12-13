#include "uart.h"

uint8 Tx_data[100];
uint8 Rx_data;
uint8 Menu_status = 1;
uint8 Menu_status_Old;
uint8 print_lock_Info,print_lock_Main,print_lock_Watch,print_lock_Game,print_lock_Thermo,print_lock_Error;

static void Uart_Programmer_Info(void);
static void Uart_Main_Menu(void);
static void Uart_Watch_Menu(void);
static void Uart_Thermometer_Menu(void);
static void Uart_Game_Menu(void);
static void Uart_Error_Menu(void);
static void Uart_Menu_Select(uint8 Rx_data);

void Uart_Receive_Init(void)
{
    Uart_Programmer_Info();
}
void Uart_Transmit(void)
{   
    switch (Menu_status)
    {
        case MENU_USERINFO:
            Uart_Programmer_Info();
        break;
        case MENU_MAIN:
            Uart_Main_Menu();
        break;    
        case MENU_WATCH:
            Uart_Watch_Menu();
        break;    
        case MENU_THERMOMETER:
            Uart_Thermometer_Menu();
        break;    
        case MENU_GAME:
            Uart_Game_Menu();
        break;    
        case MENU_ERROR:
            Uart_Error_Menu();
        break;
        default:
        break;
    }

    return;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        if(((Rx_data >= '0')&&(Rx_data <= '9'))||
           ((Rx_data >= 'a')&&(Rx_data <= 'z'))||
           ((Rx_data >= 'A')&&(Rx_data <= 'Z')))
        {
            sprintf(Tx_data,"Receive Menu information is : ");
            HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
            HAL_UART_Transmit(&UART1,&Rx_data,1, 100);
            sprintf(Tx_data,"\n\n");
            HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
            Uart_Menu_Select(Rx_data);
        }

        HAL_UART_Receive_IT(&UART1,&Rx_data,1);
    }
    return;
}

static void Uart_Menu_Select(uint8 Rx_data)
{

    Menu_status_Old = Menu_status;

    if(Menu_status == MENU_MAIN)
    {
        switch(Rx_data)
        {
            case MAIN_USERINFO_ASCII :
                Menu_status = MENU_USERINFO;
                print_lock_Info = PRINT_OUT_LOCK_OFF;
            break;
            case MAIN_WATCH_ASCII :
                Menu_status = MENU_WATCH;
                print_lock_Watch = PRINT_OUT_LOCK_OFF;
            break;
            case MAIN_THERMOMETER_ASCII :
                Menu_status = MENU_THERMOMETER;
                print_lock_Thermo = PRINT_OUT_LOCK_OFF;
            break;
            case MAIN_GAME_ASCII :
                Menu_status = MENU_GAME;
                print_lock_Game = PRINT_OUT_LOCK_OFF;
            break;     
            default:
                Menu_status = MENU_ERROR;
                print_lock_Error = PRINT_OUT_LOCK_OFF;
            break;        
        }
    }
    else if(Menu_status == MENU_WATCH)
    {
        switch(Rx_data)
        {
            case WATCH_USERINFO_ASCII :
                Menu_status = MENU_USERINFO;
                print_lock_Info = PRINT_OUT_LOCK_OFF;
            break;
            case WATCH_START_ASCII :

            break;
            case WATCH_RESET_ASCII :

            break;
            case WATCH_STOP_ASCII :

            break;
            case WATCH_DISPLAY_CURRENT_ASCII :
                Menu_status = MENU_WATCH;
                print_lock_Watch = PRINT_OUT_LOCK_OFF;         
            break;                 
            case WATCH_GOTO_MAIN_ASCII :
                Menu_status = MENU_MAIN;
                print_lock_Main = PRINT_OUT_LOCK_OFF;           
            break;     
            default:
                Menu_status = MENU_ERROR;
                print_lock_Error = PRINT_OUT_LOCK_OFF;
            break;        
        }        
    }
    else if(Menu_status == MENU_THERMOMETER)
    {
        switch(Rx_data)
        {
            case THERMO_USERINFO_ASCII :
                Menu_status = MENU_USERINFO;
                print_lock_Info = PRINT_OUT_LOCK_OFF;
            break;
            case THERMO_CELSIUS_ASCII :

            break;
            case THERMO_FAHRENHEIT_ASCII :

            break;
            case THERMO_DISPLAY_CURRENT_ASCII :
                Menu_status = MENU_THERMOMETER;
                print_lock_Watch = PRINT_OUT_LOCK_OFF;         
            break;                 
            case THERMO_GOTO_MAIN_ASCII :
                Menu_status = MENU_MAIN;
                print_lock_Main = PRINT_OUT_LOCK_OFF;           
            break;     
            default:
                Menu_status = MENU_ERROR;
                print_lock_Error = PRINT_OUT_LOCK_OFF;
            break;        
        }        
    }

    else if(Menu_status == MENU_GAME)
    {
        switch(Rx_data)
        {
            case GAME_USERINFO_ASCII :
                Menu_status = MENU_USERINFO;
                print_lock_Info = PRINT_OUT_LOCK_OFF;
            break;
            case GAME_START_ASCII :

            break;
            case GAME_DISPLAY_CURRENT_ASCII :
                Menu_status = MENU_GAME;
                print_lock_Watch = PRINT_OUT_LOCK_OFF;         
            break;                 
            case GAME_GOTO_MAIN_ASCII :
                Menu_status = MENU_MAIN;
                print_lock_Main = PRINT_OUT_LOCK_OFF;           
            break;     
            default:
                Menu_status = MENU_ERROR;
                print_lock_Error = PRINT_OUT_LOCK_OFF;
            break;        
        }        
    }
    else{}

    return;
}

static void Uart_Programmer_Info(void)
{
    if(print_lock_Info == PRINT_OUT_LOCK_OFF)
    {
        print_lock_Info = PRINT_OUT_LOCK_ON;

        sprintf(Tx_data,"- Programmer Information\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
        sprintf(Tx_data,"Student ID: 12345678\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        sprintf(Tx_data,"Name: Hong, Gildong\n\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
        HAL_UART_Receive_IT(&UART1,&Rx_data,1);
        
        switch (Menu_status_Old)
        {
            case MENU_MAIN:
                Menu_status = MENU_MAIN;
                print_lock_Main = PRINT_OUT_LOCK_OFF;
            break;
            case MENU_WATCH:
                Menu_status = MENU_WATCH;
                print_lock_Watch = PRINT_OUT_LOCK_OFF;
            break;                    
            case MENU_THERMOMETER:
                Menu_status = MENU_THERMOMETER;
                print_lock_Thermo = PRINT_OUT_LOCK_OFF;
            break;                
            case MENU_GAME:
                Menu_status = MENU_GAME;
                print_lock_Game = PRINT_OUT_LOCK_OFF;
            break;  
            default:
            break;
        }
    }
}

static void Uart_Main_Menu(void)
{
    if(print_lock_Main == PRINT_OUT_LOCK_OFF)
    {
        print_lock_Main = PRINT_OUT_LOCK_ON; 
            
        sprintf(Tx_data,"Main Menu Mode\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
        sprintf(Tx_data,"1. Watch Mode\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        sprintf(Tx_data,"2. Thermometer Mode\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);                        
        sprintf(Tx_data,"3. Game Mode\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"0. Programmer Information\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);                
        sprintf(Tx_data,"press number key to run.\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        HAL_UART_Receive_IT(&UART1,&Rx_data,1);
    }

    return;
}

static void Uart_Watch_Menu(void)
{
    if(print_lock_Watch == PRINT_OUT_LOCK_OFF)
    {
        print_lock_Watch = PRINT_OUT_LOCK_ON;        
        sprintf(Tx_data,"Watch Mode\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
        sprintf(Tx_data,"1. START Watch\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        sprintf(Tx_data,"2. Reset Watch\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);                        
        sprintf(Tx_data,"3. Stop Watch\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"0. Programmer Information\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"8. Display Current Menu\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);              
        sprintf(Tx_data,"9. Go Main Menu\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"press number key to run.\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        HAL_UART_Receive_IT(&UART1,&Rx_data,1);
    }
    return;
}
static void Uart_Thermometer_Menu(void)
{
    if(print_lock_Thermo == PRINT_OUT_LOCK_OFF)
    {
        print_lock_Thermo = PRINT_OUT_LOCK_ON;        
        sprintf(Tx_data,"Thermometer Mode\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
        sprintf(Tx_data,"1. Celsius Display\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        sprintf(Tx_data,"2. Fahrenheit Display\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);                          
        sprintf(Tx_data,"0. Programmer Information\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"8. Display Current Menu\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);              
        sprintf(Tx_data,"9. Go Main Menu\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"press number key to run.\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        HAL_UART_Receive_IT(&UART1,&Rx_data,1);
    }
    return;    
}
static void Uart_Game_Menu(void)
{
    if(print_lock_Game == PRINT_OUT_LOCK_OFF)
    {
        print_lock_Game = PRINT_OUT_LOCK_ON;       
        sprintf(Tx_data,"Game Mode\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
        sprintf(Tx_data,"1. Start Game\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);                      
        sprintf(Tx_data,"0. Programmer Information\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"8. Display Current Menu\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);              
        sprintf(Tx_data,"9. Go Main Menu\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);            
        sprintf(Tx_data,"press number key to run.\n");
        HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);    
        HAL_UART_Receive_IT(&UART1,&Rx_data,1); 
    }
    return;    
}
static void Uart_Error_Menu(void)
{
    if(print_lock_Error == PRINT_OUT_LOCK_OFF)
    {
        print_lock_Error = PRINT_OUT_LOCK_ON;        

        switch(Menu_status_Old)
        {
            case MENU_MAIN :
                sprintf(Tx_data,"Error Code: 0x000A12345678 \n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
                sprintf(Tx_data,"Description: Wrong menu item in Main Menu Mode\n\n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
                Menu_status = MENU_MAIN;
                print_lock_Main = PRINT_OUT_LOCK_OFF; 
            break;
            case MENU_WATCH :
                sprintf(Tx_data,"Error Code: 0x000B12345678 \n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
                sprintf(Tx_data,"Description: Wrong menu item in Watch Menu Mode\n\n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
                Menu_status = MENU_WATCH;
                print_lock_Watch = PRINT_OUT_LOCK_OFF;     
            break;
            case MENU_THERMOMETER :
                sprintf(Tx_data,"Error Code: 0x000C12345678 \n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
                sprintf(Tx_data,"Description: Wrong menu item in Thermometer Menu Mode\n\n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);               
                Menu_status = MENU_THERMOMETER;
                print_lock_Thermo = PRINT_OUT_LOCK_OFF;     
            break;
             case MENU_GAME :
                sprintf(Tx_data,"Error Code: 0x000D12345678 \n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
                sprintf(Tx_data,"Description: Wrong menu item in Game Menu Mode\n\n");
                HAL_UART_Transmit(&UART1,Tx_data,strlen(Tx_data), 100);
                Menu_status = MENU_GAME;
                print_lock_Game = PRINT_OUT_LOCK_OFF;     
            break;
        }
    }
    return;    
}