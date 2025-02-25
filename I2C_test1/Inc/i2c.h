#ifndef I2C_H
#define I2C_H

#include "stm32f103xb.h"

void I2C_Init(I2C_TypeDef *I2Cx, GPIO_TypeDef *GPIOx, uint8_t sclPin, uint8_t sdaPin);
uint8_t I2C_IsDeviceReady(I2C_TypeDef *I2Cx, uint8_t slaveAddr);
void I2C_Master_Transmit(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t *data, uint8_t length);
void I2C_Master_Receive(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t *buffer, uint8_t length);
void I2C_Mem_Write(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint8_t length);
void I2C_Mem_Read(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t memAddr, uint8_t *buffer, uint8_t length);

#endif // I2C_H
