
#include "esp8266.h"
#include "string.h"
#include "stdio.h"

extern char dummy[1];

uint8_t receiver_buffer[250];
uint8_t OKFlag,IPDFlag,UARTFlag,ReadyFlag;
uint16_t rxcount;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
        if(huart->Instance == USART1)
        {
            HAL_UART_Receive_IT(&huart1, dummy, 1);
			HAL_UART_Transmit(&huart4,&huart->Instance->RDR,1,10);
        }
        else if(huart->Instance == UART4)
        {   
			receiver_buffer[rxcount] = huart->Instance->RDR;
			rxcount++;
			// ok\r\n, esp module���� ���
			if((rxcount>=7)&&(receiver_buffer[rxcount-7] == 'r')&&(receiver_buffer[rxcount-6] == 'e')&&(receiver_buffer[rxcount-5] == 'a')&&(receiver_buffer[rxcount-4] == 'd')&&(receiver_buffer[rxcount-3] == 'y')&&(receiver_buffer[rxcount-2] == '\r')&&(receiver_buffer[rxcount-1] == '\n'))
			{
				ReadyFlag = 1;	
				rxcount = 0;	
				UARTFlag = 1;
				memset(receiver_buffer,0x00,sizeof(receiver_buffer));
			}		
			else if((rxcount>=4)&&(receiver_buffer[rxcount-4] == 'O')&&(receiver_buffer[rxcount-3] == 'K')&&(receiver_buffer[rxcount-2] == '\r')&&(receiver_buffer[rxcount-1] == '\n'))
			{
				OKFlag = 1;	
				rxcount = 0;	
				UARTFlag = 1;
				memset(receiver_buffer,0x00,sizeof(receiver_buffer));
			}					
			// \r\n, App���� ���, Data Receiver +IPD ~....~ \r\n
			else if((rxcount>=6)&&(receiver_buffer[rxcount-6] == '\r')&&(receiver_buffer[rxcount-5] == '\n')&&(receiver_buffer[rxcount-4] == '+')&&(receiver_buffer[rxcount-3] == 'I')&&(receiver_buffer[rxcount-2] == 'P')&&(receiver_buffer[rxcount-1] == 'D')) 
			{	// \r\nok, esp module���� ���
				IPDFlag = 1;	
				rxcount = 0;	
				UARTFlag = 1;
			}
			else if((rxcount>=6)&&(receiver_buffer[rxcount-6] == 'F')&&(receiver_buffer[rxcount-5] == 'A')&&(receiver_buffer[rxcount-4] == 'I')&&(receiver_buffer[rxcount-3] == 'L')&&(receiver_buffer[rxcount-2] == '\r')&&(receiver_buffer[rxcount-1] == '\n'))
			{
				UARTFlag = 1;
				rxcount = 0;	
				memset(receiver_buffer,0x00,sizeof(receiver_buffer));
			}
            HAL_UART_Receive_IT(&huart4, dummy, 1);
			HAL_UART_Transmit(&huart1,&huart->Instance->RDR,1,10);
        }
        else{}
}


