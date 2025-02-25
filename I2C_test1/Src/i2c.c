#include "i2c.h"

void I2C1_Init(void) {
    // Enable I2C1 and GPIOB clocks
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configure PB6 (SCL) and PB7 (SDA) as Alternate Function Open-Drain
    GPIOB->CRL &= ~((0xF << 24) | (0xF << 28));
    GPIOB->CRL |= ((0xB << 24) | (0xB << 28));

    // Reset I2C1
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    // Configure Clock (100kHz Standard Mode, PCLK1 = 8MHz)
    I2C1->CR2 = 8;  // APB1 clock = 8MHz
    I2C1->CCR = 40; // (8MHz / 100kHz) / 2 = 40
    I2C1->TRISE = 9; // (8MHz * 1µs) + 1 = 9

    // Enable I2C1, Enable ACK
    I2C1->CR1 = I2C_CR1_PE | I2C_CR1_ACK;
}

uint8_t I2C1_IsDeviceReady(uint8_t slaveAddr) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = (slaveAddr << 1);
    while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)));

    if (I2C1->SR1 & I2C_SR1_AF) {
        I2C1->SR1 &= ~I2C_SR1_AF;
        return 0; // Not Ready
    }

    (void)I2C1->SR2; // Clear ADDR
    I2C1->CR1 |= I2C_CR1_STOP;
    return 1; // Ready
}

void I2C1_Master_Transmit(uint8_t slaveAddr, uint8_t *data, uint8_t length) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = (slaveAddr << 1);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    for (uint8_t i = 0; i < length; i++) {
        while (!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = data[i];
    }

    while (!(I2C1->SR1 & I2C_SR1_BTF));
    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C1_Master_Receive(uint8_t slaveAddr, uint8_t *buffer, uint8_t length) {
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = (slaveAddr << 1) | 1;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    for (uint8_t i = 0; i < length; i++) {
        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        buffer[i] = I2C1->DR;
    }

    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C1_Slave_Transmit(uint8_t *data, uint8_t length) {
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    for (uint8_t i = 0; i < length; i++) {
        while (!(I2C1->SR1 & I2C_SR1_TXE));
        I2C1->DR = data[i];
    }

    while (!(I2C1->SR1 & I2C_SR1_BTF));
}

void I2C1_Slave_Receive(uint8_t *buffer, uint8_t length) {
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    for (uint8_t i = 0; i < length; i++) {
        while (!(I2C1->SR1 & I2C_SR1_RXNE));
        buffer[i] = I2C1->DR;
    }
}

void I2C1_Mem_Write(uint8_t slaveAddr, uint8_t memAddr, uint8_t *data, uint8_t length) {
    I2C1_Master_Transmit(slaveAddr, &memAddr, 1);
    I2C1_Master_Transmit(slaveAddr, data, length);
}

void I2C1_Mem_Read(uint8_t slaveAddr, uint8_t memAddr, uint8_t *buffer, uint8_t length) {
    I2C1_Master_Transmit(slaveAddr, &memAddr, 1);
    I2C1_Master_Receive(slaveAddr, buffer, length);
}
