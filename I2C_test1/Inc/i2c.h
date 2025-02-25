#ifndef I2C_H
#define I2C_H

#include "stm32f103xb.h"

void I2C1_Init(void);
uint8_t I2C1_IsDeviceReady(uint8_t slaveAddr);

void I2C1_Master_Transmit(uint8_t slaveAddr, uint8_t *data, uint8_t length);
void I2C1_Master_Receive(uint8_t slaveAddr, uint8_t *buffer, uint8_t length);
void I2C1_Slave_Transmit(uint8_t *data, uint8_t length);
void I2C1_Slave_Receive(uint8_t *buffer, uint8_t length);

void I2C1_Mem_Write(uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint8_t length);
void I2C1_Mem_Read(uint8_t slaveAddr, uint8_t memAddr, uint8_t *buffer, uint8_t length);

#endif
