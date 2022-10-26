
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
			if((rxcount>=7)&&(receiver_buffer[rxcount-7] == 'r')&&(receiver_buffer[rxcount-6] == 'e')&&(receiver_buffer[rxcount-5] == 'a')&&(receiver_buffer[rxcount-4] == 'd')&&(receiver_buffer[rxcount-3] == 'y')&&(receiver_buffer[rxcount-2] == 0x0D)&&(receiver_buffer[rxcount-1] == 0x0A) )
			{
				ReadyFlag = 1;	
				rxcount = 0;	
				UARTFlag = 1;
				memset(receiver_buffer,0x00,sizeof(receiver_buffer));
			}		
			else if( (receiver_buffer[rxcount-4] == 0x4F ) && (receiver_buffer[rxcount-3] == 0x4B ) && (receiver_buffer[rxcount-2] == 0x0D ) && (receiver_buffer[rxcount-1] == 0x0A) )
			{
				OKFlag = 1;	
				rxcount = 0;	
				UARTFlag = 1;
				memset(receiver_buffer,0x00,sizeof(receiver_buffer));
			}					
			// \r\n, App���� ���, Data Receiver +IPD ~....~ \r\n
			else if( (receiver_buffer[2] == 0x2B ) && (receiver_buffer[3] == 0x49 ) && (receiver_buffer[4] == 0x50 ) && (receiver_buffer[5] == 0x44 ) && (receiver_buffer[0] == 0x0D ) && (receiver_buffer[1] == 0x0A) ) 
			{	// \r\nok, esp module���� ���
				IPDFlag = 1;	
				rxcount = 0;	
				UARTFlag = 1;
			}
            HAL_UART_Receive_IT(&huart4, dummy, 1);
			HAL_UART_Transmit(&huart1,&huart->Instance->RDR,1,10);
        }
        else{}
}


