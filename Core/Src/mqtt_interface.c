#include "mqtt_interface.h"
#include "MQTTClient.h"

uint32_t MilliTimer;

MQTTClient mqttClient;
Network net; //mqtt network

uint8_t sndBuffer[MQTT_BUFFER_SIZE]; //mqtt send buffer
uint8_t rcvBuffer[MQTT_BUFFER_SIZE]; //mqtt receive buffer
uint8_t msgBuffer[MQTT_BUFFER_SIZE]; //mqtt message buffer
void MqttMessageArrived(MessageData* msg);

static void MQTT_Connect_Broker(void);
static void Clear_Tx_Buffer(uint8_t *buf,uint16_t length);
static void Uart_Transmit(uint8_t * buffer, uint16_t length);
static void ESP8266_SetModeStation(uint8_t mode);
static void ESP8266_Connect(uint8_t *ssid, uint8_t *passwd);
static void ESP8266_SetMUX(uint8_t mux);
static void ESP8266_SetServer(uint8_t set, uint16_t port);
static void ESP8266_StartTCPClient(uint8_t * ip,uint16_t port);
static uint8_t ESP8266_SendData(uint8_t * buffer,uint16_t Length);
static uint8_t ESP8266_ReceiveData(uint8_t * buffer,int *Length);
static uint8_t CheckStatus(uint8_t status);

void MQTT_InitTask(void)
{
	while(!ReadyFlag);
	ESP8266_SetModeStation(ESP8266_MODE_ALL);
    ESP8266_Connect((uint8_t *)MQTT_SSID,(uint8_t *)MQTT_PASSWORD);
    ESP8266_SetMUX(1);
	ESP8266_SetServer(1,333);
	ESP8266_StartTCPClient((uint8_t *)MQTT_BROKER_IP,MQTT_PORT);
	MQTT_Connect_Broker();
}

void MQTT_Client_Sub_Task(void)
{
	MQTTYield(&mqttClient, 5000);
}

void MQTT_Client_Pub_Task(void)
{
	const char str[] = "MQTT Test Message Transmit\n";

	MQTTMessage message;

	if(mqttClient.isconnected)
	{
		message.payload = (void*)str;
		message.payloadlen = strlen(str);

		MQTTPublish(&mqttClient, "test", &message); //publish a message
	}
}

static void MQTT_Connect_Broker(void)
{
	int ret;

	NewNetwork(&net);

	MQTTClientInit(&mqttClient, &net, 1000, sndBuffer, sizeof(sndBuffer), rcvBuffer, sizeof(rcvBuffer));

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	data.willFlag = 0;
	data.MQTTVersion = 3;
	data.clientID.cstring = "LED_RELAY_192.168.0.248";
	data.username.cstring = "";
	data.password.cstring = "";
	data.keepAliveInterval = 60;
	data.cleansession = 1;

	ret = MQTTConnect(&mqttClient, &data);

	ret = MQTTSubscribe(&mqttClient, "test", QOS0, MqttMessageArrived);
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

void NewNetwork(Network *n) 
{
	n->socket = 0; //clear
	n->mqttread = net_read; //receive function
	n->mqttwrite = net_write; //send function
	n->disconnect = net_disconnect; //disconnection function
}

int net_read(Network *n, unsigned char *buffer, int len, int timeout_ms) 
{
	uint8_t status = STATUS_FAIL;

	status = ESP8266_ReceiveData(buffer,&len);
	
	if(status == STATUS_SUCCESS)
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
	uint8_t status = STATUS_FAIL;

	status = ESP8266_SendData(buffer,len);

	if(status == STATUS_SUCCESS)
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

static void Clear_Tx_Buffer(uint8_t *buf,uint16_t length)
{
    for(uint16_t i = 0; i < length; i++)
    {
        buf[i] = 0;
    }
}

static void Uart_Transmit(uint8_t * buffer, uint16_t length)
{
	IPDFlag = 0;
	OKFlag = 0;
	UARTFlag = 0;	
	//for (uint16_t i = 0; i < length; i++) 
	//{
		HAL_UART_Transmit(&huart4,buffer,length,10);
	//}	
	/* NL/CR 전송 */
	HAL_UART_Transmit(&huart4,"\r\n",2,10);
	HAL_UART_Transmit(&huart1,buffer,length,10);
	HAL_UART_Transmit(&huart1,"\r\n",2,10);
	while(!UARTFlag);
}

static void ESP8266_SetModeStation(uint8_t mode)
{
	uint8_t buffer[64] = {0,};
	
	sprintf((char *)buffer,"AT+CWMODE_CUR=%d",mode);
	Uart_Transmit(buffer,strlen((char *)buffer));
}

static void ESP8266_Connect(uint8_t *ssid, uint8_t *passwd)
{
    uint8_t buffer[64] = {0,};

	sprintf((char *)buffer, "AT+CWJAP=\"%s\",\"%s\"", ssid, passwd);
	Uart_Transmit(buffer,strlen((char *)buffer));
}

static void ESP8266_SetMUX(uint8_t mux)
{
	uint8_t buffer[64] = {0,};

	sprintf((char *)buffer, "AT+CIPMUX=%d", mux);
	Uart_Transmit(buffer,strlen((char *)buffer));
}

static void ESP8266_SetServer(uint8_t set, uint16_t port)
{
	uint8_t buffer[64] = {0,};

	sprintf((char *)buffer, "AT+CIPSERVER=%d,%d", set, port);
	Uart_Transmit(buffer,strlen((char *)buffer));
}

static void ESP8266_StartTCPClient(uint8_t * ip,uint16_t port)
{
	uint8_t buffer[128] = {0,};

	sprintf((char *)buffer, "AT+CIPSTART=0,\"TCP\",\"%s\",%d",ip,port);
	Uart_Transmit(buffer,strlen((char *)buffer));
}

static uint8_t ESP8266_SendData(uint8_t * buffer,uint16_t Length)
{
	uint8_t buffer_internal[64]={0,};
	uint8_t status = 0;
	
	/* AT Command Transmit */
	sprintf((char *)buffer_internal, "AT+CIPSEND=0,%d", Length);
	Uart_Transmit(buffer_internal,strlen((char *)buffer_internal));
	status = CheckStatus(OKFlag);

	/* Data Transmit*/
	Uart_Transmit(buffer,Length);
	status = CheckStatus(OKFlag);	
	HAL_Delay(100);
	return status;
}

static uint8_t ESP8266_ReceiveData(uint8_t * buffer,int * Length)
{
	uint8_t buffer_internal[64]={0,};
	uint8_t status = 0;
	/* Data Receive*/
	status = CheckStatus(IPDFlag);	
	if(receiver_buffer[3]>'0')
	{
		*Length = receiver_buffer[3] - '0';
	}
	else
	{
		*Length = 0;
	}
	for(uint16_t i = 0;i < *Length;i++)
	{
		*(buffer+i) = (uint16_t)receiver_buffer[5+i];
	}

	//memset(receiver_buffer,0x00,sizeof(receiver_buffer));
	//rxcount = 0;
	return status;
}

static uint8_t CheckStatus(uint8_t status)
{
	if(status == 1)
	{
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_FAIL;
	}
}