#include "imu.h"

static void IMU_Read_Data(void);
IMU_BANK0_t IMU_BANK0;
uint8 IMU_Address;
void IMU_Control(void)
{
    IMU_Read_Data();
}

void IMU_FindAddress(void)
{
    if(HAL_OK == HAL_I2C_IsDeviceReady(&IMU_MODULE,IMU_Address,3,10))
    {
        /*do noThing*/
    }
    else
    {
        IMU_Address++;
    }
}

static void IMU_Read_Data(void)
{
    IMU_BANK0.ACCEL_XOUT_H.ACCEL_XOUT_H = 0;
}