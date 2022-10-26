#include "mqtt_interface.h"
#include "MQTTClient.h"
#include "esp8266.h"
#include <string.h>

#define MQTT_SSID  "BBUNGBBANGWORLD"
#define MQTT_PASSWORD  "jisu8730"
#define BROKER_IP	"192.168.0.30"
#define MQTT_PORT	1883
#define MQTT_BUFFER_SIZE	1024

uint32_t MilliTimer;

MQTTClient mqttClient;
Network net; //mqtt network


uint8_t sndBuffer[MQTT_BUFFER_SIZE]; //mqtt send buffer
uint8_t rcvBuffer[MQTT_BUFFER_SIZE]; //mqtt receive buffer
uint8_t msgBuffer[MQTT_BUFFER_SIZE]; //mqtt message buffer

void MqttMessageArrived(MessageData* msg);
int MqttConnectBroker(void);

void MQTT_InitTask(void)
{
	ESP8266_Init();
	HAL_Delay(2000);
    ESP8266_Connect(MQTT_SSID,MQTT_PASSWORD);
	HAL_Delay(2000);
    ESP8266_SetMUX(1);
	HAL_Delay(2000);
	ESP8266_SetServer(1,333);
	HAL_Delay(2000);
	MqttConnectBroker();
}

void MQTT_Client_Sub_Task(void)
{
	MQTTYield(&mqttClient, 3000);
}

void MQTT_Client_Pub_Task(void)
{
	const char* str = "MQTT message from STM32";
	MQTTMessage message;

	if(mqttClient.isconnected)
	{
		message.payload = (void*)str;
		message.payloadlen = strlen(str);

		MQTTPublish(&mqttClient, "mytopic", &message); //publish a message
	}
}

int MqttConnectBroker(void)
{
	int ret;

	NewNetwork(&net);
	ConnectNetwork(&net, BROKER_IP, MQTT_PORT);

	MQTTClientInit(&mqttClient, &net, 1000, sndBuffer, sizeof(sndBuffer), rcvBuffer, sizeof(rcvBuffer));

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.willFlag = 0;
	data.MQTTVersion = 3;
	data.clientID.cstring = "STM32F4";
	data.username.cstring = "";
	data.password.cstring = "";
	data.keepAliveInterval = 60;
	data.cleansession = 1;

	ret = MQTTConnect(&mqttClient, &data);
	if(ret != MQTT_SUCCESS)
	{
		printf("MQTTConnect failed.\n");
		return ret;
	}

	ret = MQTTSubscribe(&mqttClient, "test", QOS0, MqttMessageArrived);
	if(ret != MQTT_SUCCESS)
	{
		printf("MQTTSubscribe failed.\n");
		return ret;
	}

	printf("MQTT_ConnectBroker O.K.\n");
	return MQTT_SUCCESS;
}

void MqttMessageArrived(MessageData* msg)
{
	//HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin); //toggle pin when new message arrived

	MQTTMessage* message = msg->message;
	memset(msgBuffer, 0, sizeof(msgBuffer));
	memcpy(msgBuffer, message->payload,message->payloadlen);

	printf("MQTT MSG[%d]:%s\n", (int)message->payloadlen, msgBuffer);
}

//Timer functions
char TimerIsExpired(Timer *timer) 
{
	long left = timer->end_time - MilliTimer;
	return (left < 0);
}

void TimerCountdownMS(Timer *timer, unsigned int timeout) 
{
	timer->end_time = MilliTimer + timeout;
}

void TimerCountdown(Timer *timer, unsigned int timeout) 
{
	timer->end_time = MilliTimer + (timeout * 1000);
}

int TimerLeftMS(Timer *timer) 
{
	long left = timer->end_time - MilliTimer;
	return (left < 0) ? 0 : left;
}

void TimerInit(Timer *timer) 
{
	timer->end_time = 0;
}

#ifdef MQTT_LWIP_SOCKET
void NewNetwork(Network *n) 
{
	n->socket = 0; //clear
	n->mqttread = net_read; //receive function
	n->mqttwrite = net_write; //send function
	n->disconnect = net_disconnect; //disconnection function
}

int ConnectNetwork(Network *n, char *ip, int port) 
{
	ESP8266_SetServer(1,333);
	ESP8266_StartTCP(ip,port);

	return 0;
}

int net_read(Network *n, unsigned char *buffer, int len, int timeout_ms) 
{
	unsigned char connect;	
	bool status;

	status = ESP8266_Receive(connect,&len,buffer);
	
	if(status == TRUE)
	{
		return MQTT_SUCCESS;
	}
	else
	{
		return MQTT_FAILURE;
	}
}

int net_write(Network *n, unsigned char *buffer, int len, int timeout_ms) 
{
	unsigned char connect;
	bool status;
	status = ESP8266_Send(connect,len,buffer);

	if(status == TRUE)
	{
		return MQTT_SUCCESS;
	}
	else
	{
		return MQTT_FAILURE;
	}
}

void net_disconnect(Network *n) 
{
	#if 0 //TCP Data Write
	close(n->socket);
	n->socket = 0;
	#endif
}

#elif MQTT_LWIP_NETCONN
void NewNetwork(Network *n) 
{
	n->conn = NULL;
	n->buf = NULL;
	n->offset = 0;

	n->mqttread = net_read;
	n->mqttwrite = net_write;
	n->disconnect = net_disconnect;
}

int ConnectNetwork(Network *n, char *ip, int port) 
{
	err_t err;
	ip_addr_t server_ip;

	ipaddr_aton(ip, &server_ip);

	n->conn = netconn_new(NETCONN_TCP);
	if (n->conn != NULL) {
		err = netconn_connect(n->conn, &server_ip, port);

		if (err != ERR_OK) {
			netconn_delete(n->conn); //free memory
			return -1;
		}
	}

	return 0;
}

int net_read(Network *n, unsigned char *buffer, int len, int timeout_ms) 
{
	int rc;
	struct netbuf *inbuf;
	int offset = 0;
	int bytes = 0;

	while(bytes < len) {
		if(n->buf != NULL) {
			inbuf = n->buf;
			offset = n->offset;
			rc = ERR_OK;
		} else {
			rc = netconn_recv(n->conn, &inbuf);
			offset = 0;
		}

		if(rc != ERR_OK) {
			if(rc != ERR_TIMEOUT) {
				bytes = -1;
			}
			break;
		} else {
			int nblen = netbuf_len(inbuf) - offset;
			if((bytes+nblen) > len) {
				netbuf_copy_partial(inbuf, buffer+bytes, len-bytes,offset);
				n->buf = inbuf;
				n->offset = offset + len - bytes;
				bytes = len;
			} else {
				netbuf_copy_partial(inbuf, buffer+bytes, nblen, offset);
				bytes += nblen;
				netbuf_delete(inbuf);
				n->buf = NULL;
				n->offset = 0;
			}
		}
	}
	return bytes;
}

int net_write(Network *n, unsigned char *buffer, int len, int timeout_ms) 
{
	int rc = netconn_write(n->conn, buffer, len, NETCONN_NOCOPY);
	if(rc != ERR_OK) return -1;
	return len;
}

void net_disconnect(Network *n) 
{
	netconn_close(n->conn); //close session
	netconn_delete(n->conn); //free memory
	n->conn = NULL;
}
#endif


