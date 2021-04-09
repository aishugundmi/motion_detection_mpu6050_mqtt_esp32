#ifndef __MPU6050_HAL_H
#define __MPU6050_HAL_H

#include <stdint.h>  


void i2c_write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
void i2c_read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data);
void i2c_read_bytes(uint8_t dev_addr, uint8_t first_reg_addr, uint8_t length, uint8_t* data);

#endif