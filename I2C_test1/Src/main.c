#include "i2c.h"

int main(void) {
    I2C1_Init();

//    uint8_t dataToWrite = 0xAA;
//    uint8_t receivedData;


//    if (I2C1_IsDeviceReady(0x50)) {
//        I2C1_Master_Transmit(0x50, &dataToWrite, 1);
//        I2C1_Master_Receive(0x50, &receivedData, 1);
//    }

    // Memory Read/Write Example
    uint8_t memoryData[2] = {0x12, 0x34};
    uint8_t readBuffer[2];

    I2C1_Mem_Write(0x6A, 0x10, memoryData, 2);
    I2C1_Mem_Read(0x50, 0x10, readBuffer, 2);
    I2C1_Slave_Transmit(memoryData, sizeof(memoryData)-1);

    while (1);
}
