/*
 * i2c.h
 *
 * Created: 10/29/2019 6:16:03 AM
 *  Author: Muhammad Ali Moutiry
 */ 


#ifndef I2C_H_
#define I2C_H_
#include "types.h"
#include "hw_i2c.h"
#include "hw_types.h"
typedef uint8 i2cStatus;
/************************************************************************/
/* status codes for master transmitter                                  */
/************************************************************************/
#define I2C_MT_START_TRANSIMITTED                 (i2cStatus)0x08
#define I2C_MT_REPEATED_START_TRANSMITTED         (i2cStatus)0x10
#define I2C_MT_SLA_W_TRANSMITTED_ACK_RECEIVED     (i2cStatus)0x18
#define I2C_MT_SLA_W_TRANSMITTED_NOT_ACK_RECEIVED (i2cStatus)0x20
#define I2C_MT_DATA_TRANSMITTED_ACK_RECEIVED      (i2cStatus)0x28
#define I2C_MT_DATA_TRANSMITTED_NOT_ACK_RECEIVED  (i2cStatus)0x30
#define I2C_MT_ARBITRATION_LOST                   (i2cStatus)0x38
/************************************************************************/
/* status codes for master receiver                                     */
/************************************************************************/
#define I2C_MR_START_TRANSIMITTED                 (i2cStatus)0x08
#define I2C_MR_REPEATED_START_TRANSMITTED         (i2cStatus)0x10
#define I2C_MR_ARBITRATION_LOST                   (i2cStatus)0x38
#define I2C_MR_SLA_R_TRANSMITTED_ACK_RECEIVED     (i2cStatus)0x40
#define I2C_MR_SLA_R_TRANSMITTED_NOT_ACK_RECEIVED (i2cStatus)0x48
#define I2C_MR_DATA_RECEIVED_ACK_RETURNED         (i2cStatus)0x50
#define I2C_MR_DATA_RECEIVED_NOT_ACK_RETURNED     (i2cStatus)0x58
 
void init_i2c();
void i2c_start();
void i2c_stop();
void i2c_write(uint8 data);
uint8 i2c_readACK();
uint8 i2c_readNACK();
i2cStatus i2c_get_status()


#endif /* I2C_H_ */