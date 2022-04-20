#include "main.h"
#include "can.h"

uint8 Tx_Buffer[8] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
uint8 Tx_length = 8u;
FDCAN_TxHeaderTypeDef CAN1;
FDCAN_TxHeaderTypeDef CAN2;
uint8 CAN1_Start_status;
uint8 CAN2_Start_status;
uint8 CAN1_Tx_status;
uint8 CAN2_Tx_status;

void Can_Init(void)
{
    CAN1_Start_status = HAL_FDCAN_Start(&hfdcan1);
    CAN2_Start_status = HAL_FDCAN_Start(&hfdcan2);
    return;
}

void Can_Transmit(void)
{
    CAN1.Identifier=0xAAA;
    CAN1.IdType=FDCAN_STANDARD_ID;
    CAN1.TxFrameType=FDCAN_DATA_FRAME;
    CAN1.DataLength=FDCAN_DLC_BYTES_8;
    CAN1.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    CAN1.BitRateSwitch=FDCAN_BRS_OFF;
    CAN1.FDFormat=FDCAN_CLASSIC_CAN;
    CAN1.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    CAN1.MessageMarker=0;
    CAN1_Tx_status = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,&CAN1,Tx_Buffer);    
    CAN2.Identifier=0xAAA;
    CAN2.IdType=FDCAN_STANDARD_ID;
    CAN2.TxFrameType=FDCAN_DATA_FRAME;
    CAN2.DataLength=FDCAN_DLC_BYTES_8;
    CAN2.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    CAN2.BitRateSwitch=FDCAN_BRS_OFF;
    CAN2.FDFormat=FDCAN_CLASSIC_CAN;
    CAN2.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    CAN2.MessageMarker=0;
    CAN2_Tx_status = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2,&CAN2,Tx_Buffer);
    return;
}