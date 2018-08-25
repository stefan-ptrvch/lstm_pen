#ifndef __MPU9150_H__
#define __MPU9150_H__

/*-include-*/
#include "mbed.h"

/*-bit-*/
#define BIT_1               (1)
#define BIT_2               (2)
#define BIT_3               (3)
#define BIT_4               (4)
#define BIT_5               (5)
#define BIT_6               (6)

#define I2C_BIT_RATE 100000

/*-send command-*/
#define CLEAR_COMMAND       (0x00)

#define X_AXIS              (1)
#define Y_AXIS              (2)
#define Z_AXIS              (5)
#define ALL_AXIS            (X_AXIS+Y_AXIS+Z_AXIS)

/*-MPU-9150 register-*/                     //| Bit7 | Bit6 | Bit5 | Bit4 | Bit3 | Bit2 | Bit1 | Bit0 |
#define SELF_TEST_X         (0x0D)  // R/W  //|     XA_TEST[4-2]   |              XG_TEST[4-0]        |
#define SELF_TEST_Y         (0x0E)  // R/W  //|     YA_TEST[4-2]   |              YG_TEST[4-0]        |
#define SELE_TEST_Z         (0x0F)  // R/W  //|     ZA_TEST[4-2]   |              ZA_TEST[4-0]        |

#define SELF_TEST_A         (0x10)  // R/W  //|   RESERVED  | XA_TEST[1-0]| YA_TEST[1-0]| ZA_TEST[1-0]|
#define SMPLRT_DIV          (0x19)  // R/W  //|                     SMPLRT_DIV[7:0]                   |
#define CONFIG              (0x1A)  // R/W  //|   -  |   -  |  EXT_SYNC_SET[2:0] |    DLPE_CFG[2:0]   |
#define GYRO_CONFIG         (0x1B)  // R/W  //| XG_ST| YG_ST| ZG_ST| FS_SEL[1:0] |   -  |   -  |   -  |
#define ACCEL_CONFIG        (0x1C)  // R/W  //| XA_ST| YA_ST| ZA_ST| AFS_SEL[1:0]|          -         |

#define FIFO_EN             (0x23)  // R/W  //| TEMP_FIFO_EN | XG_FIFO_EN | YG_FIFO_EN | ZG_FIFO_EN | ACCEL_FIFO_EN | SLV2_FIFO_EN | SLV1_FIFO_EN | SLV0_FIFO_EN |
#define I2C_MST_CTRL        (0x24)  // R/W  //| MULT_MST_EN | WAIT_FOR_ES | SLV_3_FIFO_EN | I2C_MST_P_NSR | I2C_MST_CLK[3:0] |
#define I2C_SLV0_ADDR       (0x25)  // R/W  //| I2C_SLV0_RW |              I2C_SLV0_ADDR[6:0]         |
#define I2C_SLV0_REG        (0x26)  // R/W  //|                            I2C_SLV0_REG[7:0]          |
#define I2C_SLV0_CTRL       (0x27)  // R/W  //| I2C_SLV0_EN | I2C_SLV0_BYTE_SW | I2C_SLV0_REG_DIS | I2C_SLV0_GRP | I2C_SLV0_LEN[3:0] |
#define I2C_SLV1_ADDR       (0x28)  // R/W
#define I2C_SLV1_REG        (0x29)  // R/W
#define I2C_SLV1_CTRL       (0x2A)  // R/W
#define I2C_SLV2_ADDR       (0x2B)  // R/W
#define I2C_SLV2_REG        (0x2C)  // R/W
#define I2C_SLV2_CTRL       (0x2D)  // R/W
#define I2C_SLV3_ADDR       (0x2E)  // R/W
#define I2C_SLV3_REG        (0x2F)  // R/W

#define I2C_SLV3_CTRL       (0x30)  // R/W
#define I2C_SLV4_ADDR       (0x31)  // R/W
#define I2C_SLV4_REG        (0x32)  // R/W
#define I2C_SLV4_DO         (0x33)  // R/W
#define I2C_SLV4_CTRL       (0x34)  // R/W
#define I2C_SLV4_DI         (0x35)  // R
#define I2C_MST_STATUS      (0x36)  // R
#define INT_PIN_CFG         (0x37)  // R/W
#define INT_ENBLE           (0x38)  // R/W
#define INT_STATUS          (0x3A)  // R
#define ACCEL_XOUT_H        (0x3B)  // R    //ACCEL_XOUT[15:8]
#define ACCEL_XOUT_L        (0x3C)  // R    //ACCEL_XOUT[7:0]
#define ACCEL_YOUT_H        (0x3D)  // R    //ACCEL_YOUT[15:8]
#define ACCEL_YOUT_L        (0x3E)  // R    //ACCEL_YOUT[7:0]
#define ACCEL_ZOUT_H        (0x3F)  // R    //ACCEL_ZOUT[15:8]

#define ACCEL_ZOUT_L        (0x40)  // R    //ACCEL_ZOUT[7:0]
#define TEMP_OUT_H          (0x41)  // R
#define TEMP_OUT_L          (0x42)  // R
#define GYRO_XOUT_H         (0x43)  // R    //GYRO_XOUT[15:8]
#define GYRO_XOUT_L         (0x44)  // R    //GYRO_XOUT[7:0]
#define GYRO_YOUT_H         (0x45)  // R    //GYRO_YOUT[15:8]
#define GYRO_YOUT_L         (0x46)  // R    //GYRO_YOUT[7:0]
#define GYRO_ZOUT_H         (0x47)  // R    //GYRO_ZOUT[15:8]
#define GYRO_ZOUT_L         (0x48)  // R    //GYRO_ZOUT[7:0]
#define EXT_SENS_DATA_00    (0x49)  // R
#define EXT_SENS_DATA_01    (0x4A)  // R
#define EXT_SENS_DATA_02    (0x4B)  // R
#define EXT_SENS_DATA_03    (0x4C)  // R
#define EXT_SENS_DATA_04    (0x4D)  // R
#define EXT_SENS_DATA_05    (0x4E)  // R
#define EXT_SENS_DATA_06    (0x4F)  // R

#define EXT_SENS_DATA_07    (0x50)  // R
#define EXT_SENS_DATA_08    (0x51)  // R
#define EXT_SENS_DATA_09    (0x52)  // R
#define EXT_SENS_DATA_10    (0x53)  // R
#define EXT_SENS_DATA_11    (0x54)  // R
#define EXT_SENS_DATA_12    (0x55)  // R
#define EXT_SENS_DATA_13    (0x56)  // R
#define EXT_SENS_DATA_14    (0x57)  // R
#define EXT_SENS_DATA_15    (0x58)  // R
#define EXT_SENS_DATA_16    (0x59)  // R
#define EXT_SENS_DATA_17    (0x5A)  // R
#define EXT_SENS_DATA_18    (0x5B)  // R
#define EXT_SENS_DATA_19    (0x5C)  // R
#define EXT_SENS_DATA_20    (0x5D)  // R
#define EXT_SENS_DATA_21    (0x5E)  // R
#define EXT_SENS_DATA_22    (0x5F)  // R

#define EXT_SENS_DATA_23    (0x60)  // R
#define I2C_SLV0_DO         (0x63)  // R/W
#define I2C_SLV1_DO         (0x64)  // R/W
#define I2C_SLV2_DO         (0x65)  // R/W
#define I2C_SLV3_DO         (0x66)  // R/W
#define I2C_MST_DELAY_CTRL  (0x67)  // R/W
#define SIGNAL_PATH_RESET   (0x68)  // R/W
#define USER_CTRL           (0x6A)  // R/W
#define PWR_MGMT_1          (0x6B)  // R/W
#define PER_MGMT_2          (0x6C)  // R/W

#define FIFO_COUNTH         (0x72)  // R/W
#define FIFO_COUNTL         (0x73)  // R/W
#define FIFO_R_W            (0x74)  // R/W
#define WHO_AM_I            (0x75)  // R

/*-MPU-9150 setting command-*/
#define ACCEL_CONFIG_AFS_SEL_2      (0x00 << 3) //16384 LSB/mg
#define ACCEL_CONFIG_AFS_SEL_4      (0x01 << 3) //8192  LSB/mg
#define ACCEL_CONFIG_AFS_SEL_8      (0x02 << 3) //4096  LSB/mg
#define ACCEL_CONFIG_AFS_SEL_16     (0x03 << 3) //2048  LSB/mg

#define GYRO_CONFIG_FS_SEL_250      (0x00 << 3) //131  LSB/deg/sce
#define GYRO_CONFIG_FS_SEL_500      (0x01 << 3) //65.5 LSB/deg/sec
#define GYRO_CONFIG_FS_SEL_1000     (0x02 << 3) //32.8 LSB/deg/sec
#define GYRO_CONFIG_FS_SEL_2000     (0x03 << 3) //16.4 LSB/deg/sec

#define PWR_MGMT_1_CLKSEL_0         (0x00)      //Internal 8MHz oscillator
#define PWR_MGMT_1_CLKSEL_1         (0x01)      //PLL with X axis gyroscope reference
#define PWR_MGMT_1_CLKSEL_2         (0x02)      //PLL with Y axis gyroscope reference
#define PWR_MGMT_1_CLKSEL_3         (0x03)      //PLL with Z axis gyroscope reference
#define PWR_MGMT_1_CLKSEL_4         (0x04)      //PLL with external 32.768kHz reference
#define PWR_MGMT_1_CLKSEL_5         (0x05)      //PLL with external 19.2MHz reference
#define PWR_MGMT_1_CLKSEL_6         (0x06)      //Reserved
#define PWR_MGMT_1_CLKSEL_7         (0x07)      //Stops the clock and keeps the timing generator in reset

#define INT_PIN_DFG_I2C_BYPASS_EN   (0x02)
#define PWR_MGMT_1_DEVICE_RESET     (0x80)

/*-global_variable-*/
const int
    g_mpu9150_slave_address = (0x69 << 1);  //MPU6050   0b1101000

const double
    g_gyro_constant = ( 250.0f / 32768.0f );

extern char
    g_cmd[2],                  //command　storage
    g_acc_raw_data[6],         //receive data storage
    g_gyro_raw_data[6];

extern void mpu9150StartCommunication (void);
extern void mpu9150StopCommunication (void);
extern void Setup_MPU_9150 (void);
extern void Get_acc (void);
extern void Get_gyro (void);
extern void Get_mpu_9150 (void);
extern int  getAccelerationData (int axis);
extern int  getGyroscopeData (int axis);
extern void getMpu9150Info (void);  //scheduled for addition
extern int  getImuSensorValue (void);

#endif  /* __MPU9150_H__ */
