#include "MPU9150.h"

/*-mbed_setups-*/
I2C i2c_mpu9150_imu_sensor(D14, D15);       //sda scl

/*-global_variable-*/
char
    g_cmd[2]   = { 0x00 },                  //command　storage
    g_acc_raw_data[6]   = { 0x00 },         //receive data storage
    g_gyro_raw_data[6]  = { 0x00 };

void mpu9150StartCommunication (void)
{
    i2c_mpu9150_imu_sensor.frequency(I2C_BIT_RATE);            //i2c baud rate change
    i2c_mpu9150_imu_sensor.start();
}

void mpu9150StopCommunication (void)
{
    i2c_mpu9150_imu_sensor.stop();
}

void mpu9150ResetCommand (void)
{
    g_cmd[0] = PWR_MGMT_1;
    g_cmd[1] = PWR_MGMT_1_DEVICE_RESET;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_2, false);
}

/**************************************************
*Date         : 2014_09_12
*Function Name: Setup_MPU_9150
*Description  : Setup to MPU-9150.
*             : It have added  if statement because
*             : an error occurred in processing speed.
*             : It is also because of debugging.
*Argument     : none
*Return Value : none
**************************************************/
void Setup_MPU_9150 (void)
{
//    mpu9150ResetCommand();

//    wait(20);

    g_cmd[0] = ACCEL_CONFIG;
    g_cmd[1] = ACCEL_CONFIG_AFS_SEL_2;//(0x18);
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_2, false);

    g_cmd[0] = GYRO_CONFIG;
    g_cmd[1] = GYRO_CONFIG_FS_SEL_250;//(0x18);
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_2, false);

    g_cmd[0] = PWR_MGMT_1;
    g_cmd[1] = PWR_MGMT_1_CLKSEL_0;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_2, false);

    g_cmd[0] = INT_PIN_CFG;
    g_cmd[1] = INT_PIN_DFG_I2C_BYPASS_EN;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_2, false);
}

/**************************************************
*Date         : 2014_09_18
*Function Name: Get_acc
*Description  : Get acceleration data.
*             : It have added  if statement because
*             : an error occurred in processing speed.
*             : It is also because of debugging.
*Argument     : none
*Return Value : none
**************************************************/
void Get_acc (void)
{
 //ACCEL_
    g_cmd[0] = ACCEL_XOUT_H;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, true);
    i2c_mpu9150_imu_sensor.read(g_mpu9150_slave_address, g_acc_raw_data, BIT_6, false);
}

/**************************************************
*Date         : 2014_09_18
*Function Name: Get_gyro
*Description  : Get gyroscope data.
*             : It have added  if statement because
*             : an error occurred in processing speed.
*             : It is also because of debugging.
*Argument     : none
*Return Value : none
**************************************************/
void Get_gyro (void)
{
//GYRO_
    g_cmd[0] = GYRO_XOUT_H;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
    i2c_mpu9150_imu_sensor.read(g_mpu9150_slave_address, g_gyro_raw_data, BIT_6, false);
}

/**************************************************
*Date         :
*Function Name: Get_mpu_9150
*Description  : Get acceleration data & gyroscope data.
*             : It have added  if statement because
*             : an error occurred in processing speed.
*             : It is also because of debugging.
*Argument     : none
*Return Value : none
**************************************************/
void Get_mpu_9150 (void)
{
 //ACCEL_
    g_cmd[0] = ACCEL_XOUT_H;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, true);
    i2c_mpu9150_imu_sensor.read(g_mpu9150_slave_address, g_acc_raw_data, BIT_6, false);

//GYRO_
    g_cmd[0] = GYRO_XOUT_H;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, true);
    i2c_mpu9150_imu_sensor.read(g_mpu9150_slave_address, g_gyro_raw_data, BIT_6, false);
}

/**************************************************
*Date         : 2015_05_14
*Function Name: getAccelerationData
*Description  :
*Argument     : none
*Return Value : none
**************************************************/
int  getAccelerationData (int axis)
{
    if(axis == X_AXIS){
        g_cmd[0] = ACCEL_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == Y_AXIS){
        g_cmd[0] = ACCEL_YOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == Z_AXIS){
        g_cmd[0] = ACCEL_ZOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == (X_AXIS+Y_AXIS)){
        g_cmd[0] = ACCEL_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_4, false);
    }

    if(axis == (X_AXIS+Z_AXIS)){    //check
        g_cmd[0] = ACCEL_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);

        g_cmd[0] = ACCEL_ZOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == (Y_AXIS+Z_AXIS)){
        g_cmd[0] = ACCEL_YOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_4, false);
    }

    if(axis == ALL_AXIS){
        g_cmd[0] = ACCEL_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_6, false);
    }

return (0);
}

/**************************************************
*Date         : 2015_05_14
*Function Name: getGyroscopeData
*Description  :
*Argument     : none
*Return Value : none
**************************************************/
int  getGyroscopeData (int axis)
{
    if(axis == X_AXIS){
        g_cmd[0] = GYRO_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == Y_AXIS){
        g_cmd[0] = GYRO_YOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == Z_AXIS){
        g_cmd[0] = GYRO_ZOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == (X_AXIS+Y_AXIS)){
        g_cmd[0] = GYRO_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_4, false);
    }

    if(axis == (X_AXIS+Z_AXIS)){    //check
        g_cmd[0] = GYRO_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);

        g_cmd[0] = GYRO_ZOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_2, false);
    }

    if(axis == (Y_AXIS+Z_AXIS)){
        g_cmd[0] = GYRO_YOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_4, false);
    }

    if(axis == ALL_AXIS){
        g_cmd[0] = GYRO_XOUT_H;
        i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
        i2c_mpu9150_imu_sensor.read (g_mpu9150_slave_address, g_acc_raw_data, BIT_6, false);
    }

return (0);
}

/**************************************************
*Date         : 2015_05_23
*Function Name: getImuSensorValue
*Description  :
*Argument     : none
*Return Value : none
**************************************************/
int getImuSensorValue (void)
{
 //ACCEL_
    g_cmd[0] = ACCEL_XOUT_H;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
    i2c_mpu9150_imu_sensor.read(g_mpu9150_slave_address, g_acc_raw_data, BIT_6, false);

//GYRO_
    g_cmd[0] = GYRO_XOUT_H;
    i2c_mpu9150_imu_sensor.write(g_mpu9150_slave_address, g_cmd, BIT_1, false);
    i2c_mpu9150_imu_sensor.read(g_mpu9150_slave_address, g_gyro_raw_data, BIT_6, false);

return (0);
}
