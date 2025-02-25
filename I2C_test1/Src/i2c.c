#include "i2c.h"

#define I2C_TIMEOUT 10000  // Timeout to prevent infinite loops

void I2C_Init(I2C_TypeDef *I2Cx, GPIO_TypeDef *GPIOx, uint8_t sclPin, uint8_t sdaPin) {
    // Enable I2C Clock
    if (I2Cx == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    else if (I2Cx == I2C2) RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    // Enable GPIO Clock
    if (GPIOx == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    else if (GPIOx == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    else if (GPIOx == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configure SCL and SDA as Alternate Function Open-Drain
    uint8_t pin = sclPin;
    for (int i = 0; i < 2; i++) { // Loop for SCL and SDA
        if (pin < 8) {
            GPIOx->CRL &= ~(0xF << (pin * 4));
            GPIOx->CRL |= (0xB << (pin * 4));
        } else {
            GPIOx->CRH &= ~(0xF << ((pin - 8) * 4));
            GPIOx->CRH |= (0xB << ((pin - 8) * 4));
        }
        pin = sdaPin; // Switch to SDA for second iteration
    }

    // Reset I2C
    I2Cx->CR1 |= I2C_CR1_SWRST;
    I2Cx->CR1 &= ~I2C_CR1_SWRST;

    // Configure Clock (100kHz, assuming PCLK1 = 8MHz)
    I2Cx->CR2 = 8;
    I2Cx->CCR = 40;
    I2Cx->TRISE = 9;

    // Enable I2C, Enable ACK
    I2Cx->CR1 = I2C_CR1_PE | I2C_CR1_ACK;
}

static uint8_t I2C_WaitForFlag(volatile uint32_t *reg, uint32_t flag, uint8_t set) {
    uint32_t timeout = I2C_TIMEOUT;
    while (((*reg & flag) ? 1 : 0) != set) {
        if (--timeout == 0) return 0;
    }
    return 1;
}

uint8_t I2C_IsDeviceReady(I2C_TypeDef *I2Cx, uint8_t slaveAddr) {
    if (!(I2C_WaitForFlag(&I2Cx->SR2, I2C_SR2_BUSY, 0))) return 0;

    I2Cx->CR1 |= I2C_CR1_START;
    if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_SB, 1))) return 0;

    I2Cx->DR = (slaveAddr << 1);
    if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_ADDR | I2C_SR1_AF, 1))) return 0;

    if (I2Cx->SR1 & I2C_SR1_AF) {
        I2Cx->SR1 &= ~I2C_SR1_AF;
        return 0;
    }
    (void)I2Cx->SR2;
    I2Cx->CR1 |= I2C_CR1_STOP;
    return 1;
}

void I2C_Master_Transmit(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t *data, uint8_t length) {
    if (!(I2C_WaitForFlag(&I2Cx->SR2, I2C_SR2_BUSY, 0))) return;

    I2Cx->CR1 |= I2C_CR1_START;
    if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_SB, 1))) return;

    I2Cx->DR = (slaveAddr << 1);
    if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_ADDR, 1))) return;
    (void)I2Cx->SR2;

    for (uint8_t i = 0; i < length; i++) {
        if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_TXE, 1))) return;
        I2Cx->DR = data[i];
    }

    if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_BTF, 1))) return;
    I2Cx->CR1 |= I2C_CR1_STOP;
}

void I2C_Master_Receive(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t *buffer, uint8_t length) {
    if (!(I2C_WaitForFlag(&I2Cx->SR2, I2C_SR2_BUSY, 0))) return;

    I2Cx->CR1 |= I2C_CR1_ACK;
    I2Cx->CR1 |= I2C_CR1_START;
    if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_SB, 1))) return;

    I2Cx->DR = (slaveAddr << 1) | 1;
    if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_ADDR, 1))) return;
    (void)I2Cx->SR2;

    for (uint8_t i = 0; i < length; i++) {
        if (i == length - 1) I2Cx->CR1 &= ~I2C_CR1_ACK;
        if (!(I2C_WaitForFlag(&I2Cx->SR1, I2C_SR1_RXNE, 1))) return;
        buffer[i] = I2Cx->DR;
    }

    I2Cx->CR1 |= I2C_CR1_STOP;
    I2Cx->CR1 |= I2C_CR1_ACK;
}

void I2C_Mem_Write(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint8_t length) {
    I2C_Master_Transmit(I2Cx, slaveAddr, &memAddr, 1);
    I2C_Master_Transmit(I2Cx, slaveAddr, data, length);
}

void I2C_Mem_Read(I2C_TypeDef *I2Cx, uint8_t slaveAddr, uint8_t memAddr, uint8_t *buffer, uint8_t length) {
    I2C_Master_Transmit(I2Cx, slaveAddr, &memAddr, 1);
    I2C_Master_Receive(I2Cx, slaveAddr, buffer, length);
}
