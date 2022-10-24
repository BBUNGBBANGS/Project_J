
#include "esp8266.h"
#include "string.h"
#include "stdio.h"

Uart_Queue_t PC_Queue;
Uart_Queue_t ESP8266_Queue;

static UART_HandleTypeDef *ESP8266_pHandle;
uint8 ESP8266_LastError;

IPStruct_t ESP8266_Ip;
//uint16 Length, Port = 15598;
//uint8 Ret, Conn, FlagConn = 0;
//uint8 Buffer[QUEUE_BUFFER_LENGTH];

uint8 ESP8266_SSID[SSID_PW_LENGTH]   = "BBUNGBBANGWORLD";
uint8 ESP8266_PASSWORD[SSID_PW_LENGTH] = "jisu8730";

uint8 ESP8266_flagConnect;

char dummy[1];

static void Uart_Transmit(char *buf,uint16 length);
static void Clear_Tx_Buffer(char *buf,unsigned int length);
static void PutDataQueue(Uart_Queue_t *pQueue, uint8_t data);
static uint8_t GetDataQueue(Uart_Queue_t *pQueue);
static void ESP8266_ReplyWifi(uint8_t Connect, uint16_t Length, uint8_t *pBuffer);
static void ESP8266_Init_value(void);
static void ESP8266_SetHandle(UART_HandleTypeDef *pUart);
static bool ESP8266_SetIp(IPStruct_t * pIp);
static UART_HandleTypeDef * ESP8266_GetHandle(void);
static uint8_t * ESP8266_GetSSID(void);
static uint8_t * ESP8266_GetPassword(void);
static IPStruct_t * ESP8266_GetIp(void);
static uint8_t ESP8266_GetLastError(void);
static uint8_t ESP8266_GetData(void);
static bool ESP8266_PutData(uint8_t data);
static uint16_t ESP8266_GetDataSoo(void);
static bool ESP8266_CopyQueue(uint8_t *pDest);
static bool ESP8266_FindStringInqueue(uint8_t *pStr);
static bool ESP8266_FindSkipStringInqueue(uint8_t *pConn, uint8_t *pStr);
static void ESP8266_SendString(uint8_t *pStr);
static bool ESP8266_WaitForOK(void);
static bool ESP8266_SetModeStation(uint8 mode);
static bool ESP8266_Connect(uint8_t *ssid, uint8_t *passwd);
static bool ESP8266_SetMUX(uint8_t value);
static bool ESP8266_SetServer(uint8_t set, uint16_t port);
static bool ESP8266_CheckConnect(uint8_t *pConn);
static bool ESP8266_CheckClosed(uint8_t *pConn);
static bool ESP8266_Send(uint8_t Conn, uint16_t Length, uint8_t *pSend);
static bool ESP8266_Receive(uint8_t *pConn, uint16_t *pLength, uint8_t *pReceive);
static bool ESP8266_Close(uint8_t Conn);

void ESP8266_Init(void)
{
    char tx_buf[100] = {0,};
	uint8 j;
	ESP8266_Ip.ip.longvalue      = 172 +  30 * 256 + (uint32_t)  1 * 256 * 256 + (uint32_t) 99 * 256 * 256 * 256;
	ESP8266_Ip.subnet.longvalue  = 255 + 255 * 256 + (uint32_t)255 * 256 * 256 + (uint32_t)  0 * 256 * 256 * 256;
	ESP8266_Ip.gateway.longvalue = 172 +  30 * 256 + (uint32_t)  1 * 256 * 256 + (uint32_t)254 * 256 * 256 * 256;

    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);

    sprintf(tx_buf,"<ESP8266 Test> \n");

    Uart_Transmit(tx_buf,strlen(tx_buf));

    HAL_UART_Receive_IT(&huart1, dummy, 1);
    HAL_UART_Receive_IT(&huart4, dummy, 1);

    ESP8266_SetHandle(&huart4);

	while(1)
	{
		if(ESP8266_FindSkipStringInqueue(&j,"ready\r\n"))
		{
			break;
		}
	}
	
    ESP8266_SetModeStation(ESP8266_MODE_ALL);
    ESP8266_Connect(&ESP8266_SSID,&ESP8266_PASSWORD);
    //ESP8266_SetMUX(1);
    //ESP8266_SetServer(1,15598);
}

void ESP8266_ConnectWifi(void)
{
	uint8 test;
    uint8 Connnection,length,buffer[QUEUE_BUFFER_LENGTH];
	#if 0
    if(ESP8266_CheckConnect(&Connnection) == TRUE)
    {
        ESP8266_flagConnect |= (1 << (Connnection - '0'));
    }
    if((ESP8266_flagConnect && ESP8266_CheckClosed(&Connnection)) == TRUE)
    {
        ESP8266_flagConnect &= ~(1 << (Connnection - '0'));
    }
    if((ESP8266_flagConnect && ESP8266_Receive(&Connnection,&length,buffer)) == TRUE)
    {
        ESP8266_ReplyWifi(Connnection, length, buffer);
    }
	#endif
}

static void Uart_Transmit(char *buf,uint16 length)
{
    HAL_UART_Transmit(&huart1,buf,length,10);
}

static void Clear_Tx_Buffer(char *buf,unsigned int length)
{
    for(unsigned int i = 0; i < length; i++)
    {
        buf[i] = 0;
    }
}

static void PutDataQueue(Uart_Queue_t *pQueue, uint8_t data)
{
	if (pQueue->data == QUEUE_BUFFER_LENGTH)
    {
		GetDataQueue(pQueue);
    }
	if(data != 0)
	{
		pQueue->Buffer[pQueue->head++] = data;
	}

	if (pQueue->head == QUEUE_BUFFER_LENGTH)
    {
        pQueue->head = 0;
    } 
	pQueue->data++;    
}

static uint8_t GetDataQueue(Uart_Queue_t *pQueue)
{
	uint8_t ch;

	ch = pQueue->Buffer[pQueue->tail++];

	if (pQueue->tail == QUEUE_BUFFER_LENGTH)
    {
        pQueue->tail = 0;
    } 

	pQueue->data--;
    
	return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
        if(huart->Instance == USART1)
        {
            PutDataQueue(&PC_Queue, (uint8_t)(huart->Instance->RDR & (uint8_t)0x00FF));
            HAL_UART_Receive_IT(&huart1, dummy, 1);
			HAL_UART_Transmit(&huart4,&huart->Instance->RDR,1,10);
        }
        else if(huart->Instance == UART4)
        {   
            PutDataQueue(&ESP8266_Queue, (uint8_t)(huart->Instance->RDR & (uint8_t)0x00FF));
            HAL_UART_Receive_IT(&huart4, dummy, 1);
			HAL_UART_Transmit(&huart1,&huart->Instance->RDR,1,10);
        }
        else{}
}

static void ESP8266_ReplyWifi(uint8_t Connect, uint16_t Length, uint8_t *pBuffer)
{
	uint8_t imsiBuff[1024];

	*(pBuffer + Length) = 0;
	sprintf((char *)imsiBuff, "From Server: %s", pBuffer);
	ESP8266_Send(Connect, strlen((char *)imsiBuff), imsiBuff);
}

static void ESP8266_Init_value(void)
{
	ESP8266_LastError = NO_ERROR;
	ESP8266_pHandle = 0;
	memset(&ESP8266_Queue, 0, sizeof(ESP8266_Queue));
}

static void ESP8266_SetHandle(UART_HandleTypeDef *pUart)
{
	ESP8266_pHandle = pUart;
}

static bool ESP8266_SetIp(IPStruct_t * pIp)
{
	uint8_t Buffer[128];

	sprintf((char *)Buffer, "AT+CIPSTA_CUR=\"%d.%d.%d.%d\",\"%d.%d.%d.%d\",\"%d.%d.%d.%d\"",
			pIp->ip.val[0], pIp->ip.val[1], pIp->ip.val[2], pIp->ip.val[3],
			pIp->gateway.val[0], pIp->gateway.val[1], pIp->gateway.val[2], pIp->gateway.val[3],
			pIp->subnet.val[0], pIp->subnet.val[1], pIp->subnet.val[2], pIp->subnet.val[3]);
	ESP8266_SendString(Buffer);
	return ESP8266_WaitForOK();
}

static UART_HandleTypeDef * ESP8266_GetHandle(void)
{
	return ESP8266_pHandle;
}

static uint8_t * ESP8266_GetSSID(void)
{
	return ESP8266_SSID;
}

static uint8_t * ESP8266_GetPassword(void)
{
	return ESP8266_PASSWORD;
}

static IPStruct_t * ESP8266_GetIp(void)
{
	return &ESP8266_Ip;
}

static uint8_t ESP8266_GetLastError(void)
{
	return ESP8266_LastError;
}

static uint8_t ESP8266_GetData(void)
{
	if(ESP8266_Queue.data == 0) 
    {
		ESP8266_LastError = QUEUE_EMPTY;
		return FALSE;
	}
	uint8_t Ret = ESP8266_Queue.Buffer[ESP8266_Queue.tail++];
	ESP8266_Queue.tail %= QUEUE_BUFFER_LENGTH;
	ESP8266_Queue.data--;
	ESP8266_LastError = NO_ERROR;
	return Ret;
}

static bool ESP8266_PutData(uint8_t data)
{
	if(ESP8266_Queue.data == QUEUE_BUFFER_LENGTH) 
    {
		ESP8266_LastError = QUEUE_FULL;
		return FALSE;
	}
	ESP8266_Queue.Buffer[ESP8266_Queue.head++] = data;
	ESP8266_Queue.head %= QUEUE_BUFFER_LENGTH;
	ESP8266_Queue.data++;
	ESP8266_LastError = NO_ERROR;
	return TRUE;
}

static uint16_t ESP8266_GetDataSoo(void)
{
	return ESP8266_Queue.data;
}

static bool ESP8266_CopyQueue(uint8_t *pDest)
{
	if(ESP8266_Queue.data == 0) 
    {
		ESP8266_LastError = QUEUE_EMPTY;
		return FAIL;
	}
	for(uint16_t i = 0;i < ESP8266_Queue.data;i++) 
    {
		*(pDest + i ) = ESP8266_Queue.Buffer[(ESP8266_Queue.tail + i) % QUEUE_BUFFER_LENGTH];
	}
	ESP8266_LastError = NO_ERROR;
	return TRUE;
}

static bool ESP8266_FindStringInqueue(uint8_t *pStr)
{
	uint8_t Buffer[QUEUE_BUFFER_LENGTH] = {0,};
	uint8_t *p;

	CopyQueue(Buffer);
	if(ESP8266_LastError == QUEUE_EMPTY) 
    {
        return FALSE;
    }
	p = (uint8_t *)strstr((char *)Buffer, (char *)pStr);
	if(p == 0) 
    {
		ESP8266_LastError = NOT_FOUND;
		return FALSE;
	}
	ESP8266_LastError = NO_ERROR;
	return TRUE;
}

static bool ESP8266_FindSkipStringInqueue(uint8_t *pConn, uint8_t *pStr)
{
	uint8_t Buffer[QUEUE_BUFFER_LENGTH] = {0,};
	uint8_t *p;
	uint16_t Length;

	*pConn = 0;
	ESP8266_CopyQueue(Buffer);
	if(ESP8266_LastError == QUEUE_EMPTY) 
    {
        return FALSE;
    }
	p = strstr((char *)Buffer, (char *)pStr);
	if(p == NULL) 
    {
		ESP8266_LastError = NOT_FOUND;
		return FALSE;
	}
	*pConn = *(p - 2);
	Length = (int16_t)((int32_t)p - (int32_t)Buffer + strlen((char *)pStr));
	if(ESP8266_Queue.data < Length) 
    {
		ESP8266_LastError = DATA_NOTENOUGH;
		return FALSE;
	}
	ESP8266_Queue.data -= Length;
	ESP8266_Queue.tail += Length;
	ESP8266_Queue.tail %= QUEUE_BUFFER_LENGTH;
	ESP8266_LastError = NO_ERROR;
	return TRUE;
}

static void ESP8266_SendString(uint8_t *pStr)
{
	if(ESP8266_pHandle == NULL) 
    {
		ESP8266_LastError = HANDLE_NOTSET;
		return;
	}
	HAL_UART_Transmit(ESP8266_pHandle, pStr, strlen((char *)pStr), 10);
	HAL_UART_Transmit(ESP8266_pHandle, (uint8_t *)"\x0D\x0A", 2, 10);
	HAL_UART_Transmit(&huart1, pStr, strlen((char *)pStr), 10);
	HAL_UART_Transmit(&huart1, (uint8_t *)"\x0D\x0A", 2, 10);
	ESP8266_LastError = NO_ERROR;
}

static bool ESP8266_WaitForOK(void)
{
	uint8_t r, j;
	uint16_t ctTimeout;
	uint8_t buf[4] = "OK\r\n";

	while(1)
	{
		r = ESP8266_FindSkipStringInqueue(&j,buf);
		if(r == TRUE) 
        {
			ESP8266_LastError = NO_ERROR;
			return TRUE;
		}
		else
		{
			ctTimeout++;
			if(ctTimeout==65535)
			{
				break;
			}
		}
	}
	ESP8266_LastError = NOT_FOUND;
	return FALSE;
}

static bool ESP8266_SetModeStation(uint8 mode)
{
	uint8 buffer[64] = {0,};
	
	sprintf((char *)buffer,"AT+CWMODE_CUR=%d",mode);
	ESP8266_SendString(buffer);

	return ESP8266_WaitForOK();
}

static bool ESP8266_Connect(uint8_t *ssid, uint8_t *passwd)
{
    uint8_t Buffer[64] = {0,};
	uint8_t Buffer1[64] = {0,};

	sprintf((char *)Buffer1,"WiFi Connect\n");
	Uart_Transmit(Buffer1,strlen(Buffer1));
	Clear_Tx_Buffer(Buffer1,64);
	while(1)
	{
		sprintf((char *)Buffer, "AT+CWJAP=\"%s\",\"%s\"", ssid, passwd);
		ESP8266_SendString(Buffer);
		sprintf((char *)Buffer1,"..");
		Uart_Transmit(Buffer1,strlen(Buffer1));
		if(ESP8266_WaitForOK() == TRUE)
		{
			break;
		}
	}
	Clear_Tx_Buffer(Buffer1,64);
	sprintf((char *)Buffer1,"WiFi Connect Success\n");
	Uart_Transmit(Buffer1,strlen(Buffer1));

	return TRUE;
}

static bool ESP8266_SetMUX(uint8_t value)
{
	uint8_t Buffer[64] = {0,};

	sprintf((char *)Buffer, "AT+CIPMUX=%d", value);
	ESP8266_SendString(Buffer);
	return ESP8266_WaitForOK();
}

static bool ESP8266_SetServer(uint8_t set, uint16_t port)
{
	uint8_t Buffer[64] = {0,};

	sprintf((char *)Buffer, "AT+CIPSERVER=%d,%d", set, port);
	ESP8266_SendString(Buffer);
	return ESP8266_WaitForOK();
}

static bool ESP8266_CheckConnect(uint8_t *pConn)		// 0,CONNECT\x0D\x0A return connect number '0'
{
	return ESP8266_FindSkipStringInqueue(pConn, (uint8_t *)"CONNECT\x0D\x0A");
}

static bool ESP8266_CheckClosed(uint8_t *pConn)		// 0,CLOSED\x0D\x0A return connect number '0'
{
	return ESP8266_FindSkipStringInqueue(pConn, (uint8_t *)"CLOSED\x0D\x0A");
}

static bool ESP8266_Send(uint8_t Conn, uint16_t Length, uint8_t *pSend)
{
	uint8_t Buffer[64];
	uint16_t i;

	sprintf((char *)Buffer, "AT+CIPSEND=%c,%d", Conn, Length);
	ESP8266_SendString(Buffer);
	HAL_Delay(10);
	for(i = 0;i < Length;i++)
    {
		HAL_UART_Transmit(ESP8266_pHandle, pSend + i, 1, 10);
		HAL_UART_Transmit(&huart1, pSend + i, 1, 10);
    }

	return ESP8266_WaitForOK();
}

static bool ESP8266_Receive(uint8_t *pConn, uint16_t *pLength, uint8_t *pReceive)
{
	uint8_t *p;
	uint16_t i;					// +IPD,0,n:xxxx

	*pConn = *pLength = 0;
	if(ESP8266_FindSkipStringInqueue(pConn, (uint8_t *)"+IPD,") == FALSE)
    {
		return FALSE;
    }
	HAL_Delay(500);
	*pConn = ESP8266_GetData();
	ESP8266_GetData();		// ','
	p = pReceive;
	while(1) 
    {
		*p = ESP8266_GetData();
		if(*p == ':') 
        {
            break;
        }
		p++;
	}
	*p = 0;
	*pLength = atoi((char *)pReceive);
	if(ESP8266_Queue.data < *pLength) 
    {
		ESP8266_LastError = DATA_NOTENOUGH;
		return FALSE;
	}
	for(i = 0;i < *pLength;i++)
    {
		*(pReceive + i) = ESP8266_GetData();
    }

	ESP8266_LastError = NO_ERROR;
	return TRUE;
}

static bool ESP8266_Close(uint8_t Conn)
{
	uint8_t Buffer[64];

	sprintf((char *)Buffer, "AT+CIPCLOSE=%d", Conn);
	ESP8266_SendString(Buffer);
	return ESP8266_WaitForOK();
}


