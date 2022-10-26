#ifndef _MQTT_INTERFACE_H
#define _MQTT_INTERFACE_H

#include "main.h"

#define MQTT_LWIP_SOCKET

typedef struct Timer Timer;

struct Timer
{
	unsigned long systick_period;
	unsigned long end_time;
};

typedef struct Network Network;

struct Network
{
#ifdef MQTT_LWIP_SOCKET 
	int socket;
#elif MQTT_LWIP_NETCONN
	struct netconn *conn;
	struct netbuf *buf;
	int offset;
#endif
	int (*mqttread) (Network*, unsigned char*, int, int);
	int (*mqttwrite) (Network*, unsigned char*, int, int);
	void (*disconnect) (Network*);
};

extern uint32_t MilliTimer;

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