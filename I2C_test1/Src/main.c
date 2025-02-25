#include "stm32f103xb.h"
#include "i2c.h"

#define I2C_SLAVE_ADDR 0x90

int main(void) {
    uint8_t txData[] = {0x12, 0x34};
    uint8_t rxData[2];

    // Initialize I2C1 on GPIOB (SCL = PB6, SDA = PB7)
    I2C_Init(I2C1, GPIOB, 6, 7);

    // Check if device is ready
    if (I2C_IsDeviceReady(I2C1, I2C_SLAVE_ADDR)) {
        // Write to memory address 0x10
        I2C_Mem_Write(I2C1, I2C_SLAVE_ADDR, 0x10, txData, 2);

        // Read back from memory address 0x10
        I2C_Mem_Read(I2C1, I2C_SLAVE_ADDR, 0x10, rxData, 2);
    }

    while (1);
}
