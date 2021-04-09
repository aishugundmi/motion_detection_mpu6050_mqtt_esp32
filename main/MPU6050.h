#ifndef __MPU6050_H
#define __MPU6050_H

#include <stdint.h>

// MPU6050 Slave Device Address
#define MPU6050_Address  (0x68) // << 1)

#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40

#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42

#define MPU6050_RA_GYRO_XOUT_H 0x43
#define MPU6050_RA_GYRO_XOUT_L 0x44
#define MPU6050_RA_GYRO_YOUT_H 0x45
#define MPU6050_RA_GYRO_YOUT_L 0x46
#define MPU6050_RA_GYRO_ZOUT_H 0x47
#define MPU6050_RA_GYRO_ZOUT_L 0x48

#define MPU6050_RA_WHO_AM_I 0x75

#define PI  3.141592


// MPU6050  configuration register addresses
#define MPU6050_SMPLRT_DIV     0x19
#define MPU6050_USER_CTRL      0x6A
#define MPU6050_PWR_MGMT_1     0x6B
#define MPU6050_PWR_MGMT_2     0x6C
#define MPU6050_CONFIG         0x1A
#define MPU6050_GYRO_CONFIG    0x1B
#define MPU6050_ACCEL_CONFIG   0x1C
#define MPU6050_FIFO_EN       0x23
#define MPU6050_INT_ENABLE     0x38
#define MPU6050_ACCEL_XOUT_H   0x3B
#define MPU6050_SIGNAL_PATH_RESET   0x68

typedef struct
{
    int16_t Ax;
	int16_t Ay;
	int16_t Az;

	int16_t temp;

	int16_t Gx;
	int16_t Gy;
	int16_t Gz;

} mpu_data_t;

void MPU6050_Init(void);
int read_mpu(mpu_data_t *tmp);


#endif