#ifndef _MQTT_INTERFACE_H
#define _MQTT_INTERFACE_H

#include "main.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define MQTT_BUFFER_SIZE	1024
#define MQTT_SSID  		"BBUNGBBANGWORLD"
#define MQTT_PASSWORD  "jisu8730"
#define MQTT_BROKER_IP	"192.168.0.30"
#define MQTT_PORT	1883

#define ESP8266_MODE_STATION	1
#define ESP8266_MODE_AP			2
#define ESP8266_MODE_ALL		3

#define STATUS_SUCCESS	1
#define STATUS_FAIL		2

typedef struct Timer Timer;

struct Timer
{
	unsigned long systick_period;
	unsigned long end_time;
};

typedef struct Network Network;

struct Network
{
	int socket;
	int (*mqttread) (Network*, unsigned char*, int, int);
	int (*mqttwrite) (Network*, unsigned char*, int, int);
	void (*disconnect) (Network*);
};

extern uint32_t MilliTimer;

extern uint8_t UARTFlag;
extern uint8_t OKFlag;
extern uint8_t IPDFlag;
extern uint8_t ReadyFlag;
extern char receiver_buffer[250];
extern uint16_t rxcount;

extern void MQTT_InitTask(void);
extern void MQTT_Client_Sub_Task(void);
extern void MQTT_Client_Pub_Task(void);

extern void InitTimer(Timer*);
extern char TimerIsExpired(Timer*);
extern void TimerCountdownMS(Timer*, unsigned int);
extern void TimerCountdown(Timer*, unsigned int);
extern int  TimerLeftMS(Timer*);

extern int  net_read(Network*, unsigned char*, int, int);
extern int  net_write(Network*, unsigned char*, int, int);
extern void net_disconnect(Network*);
extern void NewNetwork(Network*);
extern int  ConnectNetwork(Network*, char*, int);

#endif