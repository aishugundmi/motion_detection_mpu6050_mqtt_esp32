#include "MPU6050_HAL.h"
#include "i2c.h"

void i2c_read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data)
{
    i2c_read_reg(dev_addr, reg_addr, data, 1);
}


// read multiple bytes
void i2c_read_bytes(uint8_t dev_addr, uint8_t first_reg_addr, uint8_t length, uint8_t* data)
{
      i2c_read_reg(dev_addr, first_reg_addr, data, length);
}


void i2c_write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
    i2c_write_reg(dev_addr, reg_addr, data);
}
