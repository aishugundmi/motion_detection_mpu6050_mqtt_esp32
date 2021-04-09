#include "MPU6050.h"
#include "MPU6050_HAL.h"
#include "i2c.h"




 
// configure MPU6050
void MPU6050_Init(void)
{
    i2c_write_byte(MPU6050_Address, MPU6050_SMPLRT_DIV, 0x4F);  //(8000/100)-1=79
    i2c_write_byte(MPU6050_Address, MPU6050_PWR_MGMT_1, 0x01);
    i2c_write_byte(MPU6050_Address, MPU6050_PWR_MGMT_2, 0x00);
    i2c_write_byte(MPU6050_Address, MPU6050_CONFIG, 0x00);
    //  i2c_write_byte(MPU6050_Address, MPU6050_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
    i2c_write_byte(MPU6050_Address, MPU6050_GYRO_CONFIG, (1<<3)|(1<<4));//set +/-2000degree/second full scale
    i2c_write_byte(MPU6050_Address, MPU6050_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
    i2c_write_byte(MPU6050_Address, MPU6050_FIFO_EN, 0x00);
    i2c_write_byte(MPU6050_Address, MPU6050_INT_ENABLE, 0x01);
    i2c_write_byte(MPU6050_Address, MPU6050_SIGNAL_PATH_RESET, 0x00);
    i2c_write_byte(MPU6050_Address, MPU6050_USER_CTRL, 0x00);
}


int read_mpu(mpu_data_t *tmp)
{
    uint8_t buff[14];
    i2c_read_bytes(MPU6050_Address, 0x3B, 14, buff);

    tmp->Ax = ((((uint16_t)buff[0] << 8) & 0xFF00) | buff[1]);
    tmp->Ay = ((((uint16_t)buff[2] << 8) & 0xFF00) | buff[3]);
    tmp->Az = ((((uint16_t)buff[4] << 8) & 0xFF00) | buff[5]);

	tmp->temp = ((((uint16_t)buff[6] << 8) & 0xFF00) | buff[7]);

	tmp->Gx = ((((uint16_t)buff[8] << 8) & 0xFF00) | buff[9]);
	tmp->Gy = ((((uint16_t)buff[10] << 8) & 0xFF00) | buff[11]);
	tmp->Gz = ((((uint16_t)buff[12] << 8) & 0xFF00) | buff[13]);

	return 0;
}


