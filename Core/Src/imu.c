#include "imu.h"

static void IMU_Read_Data(void);
IMU_BANK0_t IMU_BANK0;
void IMU_Control(void)
{
    IMU_Read_Data();
}

static void IMU_Read_Data(void)
{
    IMU_BANK0.ACCEL_XOUT_H.ACCEL_XOUT_H = 0;
}