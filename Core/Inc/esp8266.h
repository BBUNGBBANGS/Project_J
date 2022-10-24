#ifndef _ESP8266_H
#define _ESP8266_H

#include "main.h"

#define ESP8266_MODE_STATION	1
#define ESP8266_MODE_AP			2
#define ESP8266_MODE_ALL		3

#define QUEUE_BUFFER_LENGTH 1024
#define SSID_PW_LENGTH		16

#define NO_ERROR		0
#define NOT_FOUND		0xFF
#define HANDLE_NOTSET		1
#define QUEUE_EMPTY		10
#define QUEUE_FULL		11
#define DATA_NOTENOUGH		12

#define WAIT_RESPOND_TIME		100
#define WAIT_REPETE			1000

#define FAIL			0
#define SUCCESS			1

typedef union 
{
	uint8 val[4];
	uint32 longvalue;
} IP_t;

typedef struct 
{
	IP_t ip;
	IP_t subnet;
	IP_t gateway;
} IPStruct_t;

typedef struct
{
	uint16 head;
    uint16 tail;
    uint16 data;
	uint8 Buffer[QUEUE_BUFFER_LENGTH];
}Uart_Queue_t;

extern void ESP8266_Init(void);
extern void ESP8266_ConnectWifi(void);

#endif