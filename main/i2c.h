#ifndef __i2c_h
#define __i2c_h

#include <stdint.h> 

#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ    /*!< I2C master read */
#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0           /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                 /*!< I2C ack value */
#define NACK_VAL 0x1                /*!< I2C nack value */


void i2c_init(void);
void i2c_read_reg(uint8_t chip_addr, uint8_t data_addr, uint8_t* data, uint8_t size);
void i2c_write_reg(uint8_t chip_addr, uint8_t data_addr, uint8_t data);


#endif 