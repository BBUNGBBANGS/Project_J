#include "main.h"

#define IMU_ADDR0ESS             (0x68)

#define IMU_AD0_ENABLE          (0x01)

#define IMU_MODULE              (hi2c1)

/* USER BANK 0 REGISTER MAP */
#define IMU_ADDR0_WHO_AM_I                   (0x00)
#define IMU_ADDR0_USER_CTRL                  (0x03)
#define IMU_ADDR0_LP_CONFIG                  (0x05)
#define IMU_ADDR0_PWR_MGMT_1                 (0x06)
#define IMU_ADDR0_PWR_MGMT_2                 (0x07)
#define IMU_ADDR0_INT_PIN_CFG                (0x0F)
#define IMU_ADDR0_INT_ENABLE                 (0x10)
#define IMU_ADDR0_INT_ENABLE_1               (0x11)
#define IMU_ADDR0_INT_ENABLE_2               (0x12)
#define IMU_ADDR0_NT_ENABLE_3                (0x13)
#define IMU_ADDR0_I2C_MST_STATUS3            (0x17)
#define IMU_ADDR0_INT_STATUS                 (0x19)
#define IMU_ADDR0_INT_STATUS_1               (0x1A)
#define IMU_ADDR0_INT_STATUS_2               (0x1B)
#define IMU_ADDR0_INT_STATUS_3               (0x1C)
#define IMU_ADDR0_DELAY_TIMEH                (0x28)
#define IMU_ADDR0_DELAY_TIMEL                (0x29)
#define IMU_ADDR0_ACCEL_XOUT_H               (0x2D)
#define IMU_ADDR0_ACCEL_XOUT_L               (0x2E)
#define IMU_ADDR0_ACCEL_YOUT_H               (0x2F)
#define IMU_ADDR0_ACCEL_YOUT_L               (0x30)
#define IMU_ADDR0_ACCEL_ZOUT_H               (0x31)
#define IMU_ADDR0_ACCEL_ZOUT_L               (0x32)
#define IMU_ADDR0_GYRO_XOUT_H                (0x33)
#define IMU_ADDR0_GYRO_XOUT_L                (0x34)
#define IMU_ADDR0_GYRO_YOUT_H                (0x35)
#define IMU_ADDR0_GYRO_YOUT_L                (0x36)
#define IMU_ADDR0_GYRO_ZOUT_H                (0x37)
#define IMU_ADDR0_GYRO_ZOUT_L                (0x38)
#define IMU_ADDR0_TEMP_OUT_H                 (0x39)
#define IMU_ADDR0_TEMP_OUT_L                 (0x3A)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_00       (0x3B)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_01       (0x3C)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_02       (0x3D)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_03       (0x3E)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_04       (0x3F)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_05       (0x40)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_06       (0x41)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_07       (0x42)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_08       (0x43)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_09       (0x44)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_10       (0x45)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_11       (0x46)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_12       (0x47)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_13       (0x48)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_14       (0x49)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_15       (0x4A)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_16       (0x4B)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_17       (0x4C)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_18       (0x4D)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_19       (0x4E)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_20       (0x50)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_21       (0x51)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_22       (0x52)
#define IMU_ADDR0_EXT_SLV_SENS_DATA_23       (0x53)
#define IMU_ADDR0_FIFO_EN_1                  (0x66)
#define IMU_ADDR0_FIFO_EN_2                  (0x67)
#define IMU_ADDR0_FIFO_RST                   (0x68)
#define IMU_ADDR0_FIFO_MODE                  (0x69)
#define IMU_ADDR0_FIFO_COUNTH                (0x70)
#define IMU_ADDR0_FIFO_COUNTL                (0x71)
#define IMU_ADDR0_FIFO_R_W                   (0x72)
#define IMU_ADDR0_DATA_RDY_STATUS            (0x74)
#define IMU_ADDR0_FIFO_CFG                   (0x76)
#define IMU_ADDR0_REG_BANK_SEL               (0x7F)

/* USER BANK 1 REGISTER MAP */
#define IMU_ADDR1_SELF_TEST_X_GYRO           (0x02)
#define IMU_ADDR1_SELF_TEST_Y_GYRO           (0x03)
#define IMU_ADDR1_SELF_TEST_Z_GYRO           (0x04)
#define IMU_ADDR1_SELF_TEST_X_ACCEL          (0x0E)
#define IMU_ADDR1_SELF_TEST_Y_ACCEL          (0x0F)
#define IMU_ADDR1_SELF_TEST_Z_ACCEL          (0x10)
#define IMU_ADDR1_XA_OFFS_H                  (0x14)
#define IMU_ADDR1_XA_OFFS_L                  (0x15)
#define IMU_ADDR1_YA_OFFS_H                  (0x17)
#define IMU_ADDR1_YA_OFFS_L                  (0x18)
#define IMU_ADDR1_ZA_OFFS_H                  (0x1A)
#define IMU_ADDR1_ZA_OFFS_L                  (0x1B)
#define IMU_ADDR1_TIMEBASE_CORRECTION_PLL    (0x28)
#define IMU_ADDR1_REG_BANK_SEL               (0x7F)

/* USER BANK 2 REGISTER MAP */
#define IMU_ADDR2_GYRO_SMPLRT_DIV            (0x00)
#define IMU_ADDR2_GYRO_CONFIG_1              (0x01)
#define IMU_ADDR2_GYRO_CONFIG_2              (0x02)
#define IMU_ADDR2_XG_OFFS_USRH               (0x03)
#define IMU_ADDR2_XG_OFFS_USRL               (0x04)
#define IMU_ADDR2_YG_OFFS_USRH               (0x05)
#define IMU_ADDR2_YG_OFFS_USRL               (0x06)
#define IMU_ADDR2_ZG_OFFS_USRH               (0x07)
#define IMU_ADDR2_ZG_OFFS_USRL               (0x08)
#define IMU_ADDR2_ODR_ALIGN_EN               (0x09)
#define IMU_ADDR2_ACCEL_SMPLRT_DIV_1         (0x10)
#define IMU_ADDR2_ACCEL_SMPLRT_DIV_2         (0x11)
#define IMU_ADDR2_ACCEL_INTEL_CTRL           (0x12)
#define IMU_ADDR2_ACCEL_WOM_THR              (0x13)
#define IMU_ADDR2_ACCEL_CONFIG               (0x14)
#define IMU_ADDR2_ACCEL_CONFIG_2             (0x15)
#define IMU_ADDR2_FSYNC_CONFIG               (0x52)
#define IMU_ADDR2_TEMP_CONFIG                (0x53)
#define IMU_ADDR2_MOD_CTRL_USR               (0x54)
#define IMU_ADDR2_REG_BANK_SEL               (0x7F)

/* USER BANK 3 REGISTER MAP */
#define IMU_ADDR3_I2C_MST_ODR_CONFIG         (0x00)
#define IMU_ADDR3_I2C_MST_CTRL               (0x01)
#define IMU_ADDR3_I2C_MST_DELAY_CTRL         (0x02)
#define IMU_ADDR3_I2C_SLV0_ADDR              (0x03)
#define IMU_ADDR3_I2C_SLV0_REG               (0x04)
#define IMU_ADDR3_I2C_SLV0_CTRL              (0x05)
#define IMU_ADDR3_I2C_SLV0_DO                (0x06)
#define IMU_ADDR3_I2C_SLV1_ADDR              (0x07)
#define IMU_ADDR3_I2C_SLV1_REG               (0x08)
#define IMU_ADDR3_I2C_SLV1_CTRL              (0x09)
#define IMU_ADDR3_I2C_SLV1_DO                (0x0A)
#define IMU_ADDR3_I2C_SLV2_ADDR              (0x0B)
#define IMU_ADDR3_I2C_SLV2_REG               (0x0C)
#define IMU_ADDR3_I2C_SLV2_CTRL              (0x0D)
#define IMU_ADDR3_I2C_SLV2_DO                (0x0E)
#define IMU_ADDR3_I2C_SLV3_ADDR              (0x0F)
#define IMU_ADDR3_I2C_SLV3_REG               (0x10)
#define IMU_ADDR3_I2C_SLV3_CTRL              (0x11)
#define IMU_ADDR3_I2C_SLV3_DO                (0x12)
#define IMU_ADDR3_I2C_SLV4_ADDR              (0x13)
#define IMU_ADDR3_I2C_SLV4_REG               (0x14)
#define IMU_ADDR3_I2C_SLV4_CTRL              (0x15)
#define IMU_ADDR3_I2C_SLV4_DO                (0x16)
#define IMU_ADDR3_I2C_SLV4_DI                (0x17)
#define IMU_ADDR3_REG_BANK_SEL               (0x7F)

typedef struct 
{
   uint8 WHO_AM_I:8; /*Register to indicate to user which device is being accessed.The value for ICM-20948 is 0xEA*/
}WHO_AM_I_t;

typedef struct 
{
    uint8 RESERVED:1; 
    uint8 I2C_MST_RST:1;
    uint8 SRAM_RST:1;
    uint8 DMP_RST:1;
    uint8 I2C_IF_DIS:1;
    uint8 I2C_MST_EN:1;
    uint8 FIFO_EN:1;
    uint8 DMP_EN:1;
}USER_CTRL_t;

typedef struct
{
    uint8 RESERVED:1;
    uint8 I2C_MST_CYCLE:1;
    uint8 ACCEL_CYCLE:1;
    uint8 GYRO_CYCLE:1;
    uint8 RESERVED1:4;
}LP_CONFIG_t;

typedef struct
{
    uint8 CLKSEL:3;
    uint8 TEMP_DIS:1;
    uint8 RESERVED:1;
    uint8 LP_EN:1;
    uint8 SLEEP:1;
    uint8 DEVICE_RESET:1; 
}PWR_MGMT_1_t;

typedef struct
{
    uint8 DISABLE_GYRO:3;
    uint8 DISABLE_ACCEL:3;
    uint8 RESERVED:2;
}PWR_MGMT_2_t;

typedef struct
{
    uint8 RESERVED:1;
    uint8 BYPASS_EN:1;
    uint8 FSYNC_INT_MODE_EN:1;
    uint8 ACTL_FSYNC:1;
    uint8 INT_ANYRD_2CLEAR:1;
    uint8 INT1_LATCH__EN:1;
    uint8 INT1_OPEN:1;
    uint8 INT1_ACTL:1;
}INT_PIN_CFG_t;

typedef struct
{
    uint8 I2C_MST_INT_EN:1;
    uint8 DMP_INT1_EN:1;
    uint8 PLL_RDY_EN:1;
    uint8 WOM_INT_EN:1;
    uint8 RESERVED:3;
    uint8 REG_WOF_EN:1;
}INT_ENABLE_t;

typedef struct
{
    uint8 RAW_DATA_0_RDY_EN:1;
    uint8 RESERVED:7;
}INT_ENABLE_1_t;

typedef struct
{
    uint8 FIFO_OVERFLOW_EN:5;
    uint8 RESERVED:3;
}INT_ENABLE_2_t;

typedef struct
{
    uint8 FIFO_WM_EN:5;
    uint8 RESERVED:3;
}INT_ENABLE_3_t;

typedef struct
{
    uint8 I2C_SLV0_NACK:1;
    uint8 I2C_SLV1_NACK:1;
    uint8 I2C_SLV2_NACK:1;
    uint8 I2C_SLV3_NACK:1;
    uint8 I2C_SLV4_NACK:1;
    uint8 I2C_LOST_ARB:1;
    uint8 I2C_SLV4_DONE:1;     
    uint8 PASS_THROUGH:1;                  
}I2C_MST_STATUS_t;

typedef struct
{
    uint8 I2C_MST_INT:1;
    uint8 DMP_INT1:1;
    uint8 PLL_RDY_INT:1;
    uint8 WOM_INT:1;
    uint8 RESERVED:4;           
}INT_STATUS_t;

typedef struct
{
    uint8 RAW_DATA_0_RDY_INT:1;
    uint8 RESERVED:7;           
}INT_STATUS_1_t;

typedef struct
{
    uint8 FIFO_OVERFLOW_INT:5;
    uint8 RESERVED:3;           
}INT_STATUS_2_t;

typedef struct
{
    uint8 FIFO_WM_INT:5;
    uint8 RESERVED:3;           
}INT_STATUS_3_t;

typedef struct
{
    uint8 DELAY_TIMEH:8;
}DELAY_TIMEH_t;

typedef struct
{
    uint8 DELAY_TIMEL:8;
}DELAY_TIMEL_t;

typedef struct
{
    uint8 ACCEL_XOUT_H:8;
}ACCEL_XOUT_H_t;

typedef struct
{
    uint8 ACCEL_XOUT_L:8;
}ACCEL_XOUT_L_t;

typedef struct
{
    uint8 ACCEL_YOUT_H:8;
}ACCEL_YOUT_H_t;

typedef struct
{
    uint8 ACCEL_YOUT_L:8;
}ACCEL_YOUT_L_t;

typedef struct
{
    uint8 ACCEL_ZOUT_H:8;
}ACCEL_ZOUT_H_t;

typedef struct
{
    uint8 ACCEL_XOUT_L:8;
}ACCEL_ZOUT_L_t;

typedef struct
{
    uint8 GYRO_XOUT_H:8;
}GYRO_XOUT_H_t;

typedef struct
{
    uint8 GYRO_XOUT_L:8;
}GYRO_XOUT_L_t;

typedef struct
{
    uint8 GYRO_YOUT_H:8;
}GYRO_YOUT_H_t;

typedef struct
{
    uint8 GYRO_YOUT_L:8;
}GYRO_YOUT_L_t;

typedef struct
{
    uint8 GYRO_ZOUT_H:8;
}GYRO_ZOUT_H_t;

typedef struct
{
    uint8 GYRO_ZOUT_L:8;
}GYRO_ZOUT_L_t;

typedef struct
{
    uint8 TEMP_OUT_H:8;
}TEMP_OUT_H_t;

typedef struct
{
    uint8 TEMP_OUT_L:8;
}TEMP_OUT_L_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_00:8;
}EXT_SLV_SENS_DATA_00_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_01:8;
}EXT_SLV_SENS_DATA_01_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_02:8;
}EXT_SLV_SENS_DATA_02_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_03:8;
}EXT_SLV_SENS_DATA_03_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_04:8;
}EXT_SLV_SENS_DATA_04_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_05:8;
}EXT_SLV_SENS_DATA_05_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_06:8;
}EXT_SLV_SENS_DATA_06_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_07:8;
}EXT_SLV_SENS_DATA_07_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_08:8;
}EXT_SLV_SENS_DATA_08_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_09:8;
}EXT_SLV_SENS_DATA_09_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_10:8;
}EXT_SLV_SENS_DATA_10_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_11:8;
}EXT_SLV_SENS_DATA_11_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_12:8;
}EXT_SLV_SENS_DATA_12_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_13:8;
}EXT_SLV_SENS_DATA_13_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_14:8;
}EXT_SLV_SENS_DATA_14_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_15:8;
}EXT_SLV_SENS_DATA_15_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_16:8;
}EXT_SLV_SENS_DATA_16_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_17:8;
}EXT_SLV_SENS_DATA_17_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_18:8;
}EXT_SLV_SENS_DATA_18_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_19:8;
}EXT_SLV_SENS_DATA_19_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_20:8;
}EXT_SLV_SENS_DATA_20_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_21:8;
}EXT_SLV_SENS_DATA_21_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_22:8;
}EXT_SLV_SENS_DATA_22_t;

typedef struct
{
    uint8 EXT_SLV_SENS_DATA_23:8;
}EXT_SLV_SENS_DATA_23_t;

typedef struct
{
    uint8 SLV_0_FIFO_EN:1;
    uint8 SLV_1_FIFO_EN:1;
    uint8 SLV_2_FIFO_EN:1;
    uint8 SLV_3_FIFO_EN:1;
    uint8 RESERVED:4;                
}FIFO_EN_1_t;

typedef struct
{
    uint8 TEMP_FIFO_EN:1;
    uint8 GYRO_X_FIFO_EN:1;
    uint8 GYRO_Y_FIFO_EN:1;
    uint8 GYRO_Z_FIFO_EN:1;
    uint8 ACCEL_FIFO_EN:1;
    uint8 RESERVED:3;  
}FIFO_EN_2_t;

typedef struct
{
    uint8 FIFO_RESET:5;
    uint8 RESERVED:3;
}FIFO_RST_t;

typedef struct
{
    uint8 FIFO_MODE:5;
    uint8 RESERVED:3;
}FIFO_MODE_t;

typedef struct
{
    uint8 FIFO_CNT:5;
    uint8 RESERVED:3;
}FIFO_COUNTH_t;

typedef struct
{
    uint8 FIFO_CNT:8;
}FIFO_COUNTL_t;

typedef struct
{
    uint8 FIFO_R_W:8;
}FIFO_R_W_t;

typedef struct
{
    uint8 RAW_DATA_RDY:4;
    uint8 RESERVED:3;
    uint8 WOF_STATUS:1;
}DATA_RDY_STATUS_t;

typedef struct
{
    uint8 FIFO_CFG:1;
    uint8 RESERVED:7;
}FIFO_CFG_t;

typedef struct
{
    uint8 RESERVED:4;
    uint8 USER_BANK:2;
    uint8 RESERVED1:2;
}REG_BANK_SEL_t;

typedef struct
{
    WHO_AM_I_t WHO_AM_I;  
    USER_CTRL_t USER_CTRL;
    LP_CONFIG_t LP_CONFIG;
    PWR_MGMT_1_t PWR_MGMT_1;
    PWR_MGMT_2_t PWR_MGMT_2;
    INT_PIN_CFG_t INT_PIN_CFG;
    INT_ENABLE_t INT_ENABLE;
    INT_ENABLE_1_t INT_ENABLE_1;
    INT_ENABLE_2_t INT_ENABLE_2;
    INT_ENABLE_3_t INT_ENABLE_3;
    I2C_MST_STATUS_t I2C_MST_STATUS;
    INT_STATUS_t INT_STATUS;
    INT_STATUS_1_t INT_STATUS_1;
    INT_STATUS_2_t INT_STATUS_2;
    INT_STATUS_3_t INT_STATUS_3;
    DELAY_TIMEH_t DELAY_TIMEH;
    DELAY_TIMEL_t DELAY_TIMEL;
    ACCEL_XOUT_H_t ACCEL_XOUT_H;
    ACCEL_XOUT_L_t ACCEL_XOUT_L;
    ACCEL_YOUT_H_t ACCEL_YOUT_H;
    ACCEL_YOUT_L_t ACCEL_YOUT_L;
    ACCEL_ZOUT_H_t ACCEL_ZOUT_H;
    ACCEL_ZOUT_L_t ACCEL_ZOUT_L;
    GYRO_XOUT_H_t GYRO_XOUT_H;
    GYRO_XOUT_L_t GYRO_XOUT_L;
    GYRO_YOUT_H_t GYRO_YOUT_H;
    GYRO_YOUT_L_t GYRO_YOUT_L;
    GYRO_ZOUT_H_t GYRO_ZOUT_H;
    GYRO_ZOUT_L_t GYRO_ZOUT_L;
    TEMP_OUT_H_t TEMP_OUT_H;
    TEMP_OUT_L_t TEMP_OUT_L;
    EXT_SLV_SENS_DATA_00_t EXT_SLV_SENS_DATA_00;
    EXT_SLV_SENS_DATA_01_t EXT_SLV_SENS_DATA_01;
    EXT_SLV_SENS_DATA_02_t EXT_SLV_SENS_DATA_02;
    EXT_SLV_SENS_DATA_03_t EXT_SLV_SENS_DATA_03;
    EXT_SLV_SENS_DATA_04_t EXT_SLV_SENS_DATA_04;
    EXT_SLV_SENS_DATA_05_t EXT_SLV_SENS_DATA_05;
    EXT_SLV_SENS_DATA_06_t EXT_SLV_SENS_DATA_06;
    EXT_SLV_SENS_DATA_07_t EXT_SLV_SENS_DATA_07;
    EXT_SLV_SENS_DATA_08_t EXT_SLV_SENS_DATA_08;
    EXT_SLV_SENS_DATA_09_t EXT_SLV_SENS_DATA_09;
    EXT_SLV_SENS_DATA_10_t EXT_SLV_SENS_DATA_10;
    EXT_SLV_SENS_DATA_11_t EXT_SLV_SENS_DATA_11;
    EXT_SLV_SENS_DATA_12_t EXT_SLV_SENS_DATA_12;
    EXT_SLV_SENS_DATA_13_t EXT_SLV_SENS_DATA_13;
    EXT_SLV_SENS_DATA_14_t EXT_SLV_SENS_DATA_14;
    EXT_SLV_SENS_DATA_15_t EXT_SLV_SENS_DATA_15;
    EXT_SLV_SENS_DATA_16_t EXT_SLV_SENS_DATA_16;
    EXT_SLV_SENS_DATA_17_t EXT_SLV_SENS_DATA_17;
    EXT_SLV_SENS_DATA_18_t EXT_SLV_SENS_DATA_18;
    EXT_SLV_SENS_DATA_19_t EXT_SLV_SENS_DATA_19;
    EXT_SLV_SENS_DATA_20_t EXT_SLV_SENS_DATA_20;
    EXT_SLV_SENS_DATA_21_t EXT_SLV_SENS_DATA_21;
    EXT_SLV_SENS_DATA_22_t EXT_SLV_SENS_DATA_22;
    EXT_SLV_SENS_DATA_23_t EXT_SLV_SENS_DATA_23;
    FIFO_EN_1_t FIFO_EN_1;
    FIFO_EN_2_t FIFO_EN_2;
    FIFO_RST_t FIFO_RST;
    FIFO_MODE_t FIFO_MODE;
    FIFO_COUNTH_t FIFO_COUNTH;
    FIFO_COUNTL_t FIFO_COUNTL;
    FIFO_R_W_t FIFO_R_W;
    DATA_RDY_STATUS_t DATA_RDY_STATUS;
    FIFO_CFG_t FIFO_CFG;
    REG_BANK_SEL_t REG_BANK_SEL;
}IMU_BANK0_t;

extern void IMU_Control(void);
extern void IMU_FindAddress(void);