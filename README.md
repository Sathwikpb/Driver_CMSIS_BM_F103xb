# I2C1 Peripheral Driver for STM32

This repository provides an implementation of an I2C1 peripheral driver for an STM32 microcontroller. The driver includes functions for initializing I2C1, checking device readiness, transmitting and receiving data, and performing memory read/write operations.

## Features
- Master and Slave mode support
- Data transmission and reception
- Memory read/write operations
- Device readiness check

## Getting Started
### Prerequisites
- STM32CubeIDE or Keil MDK
- STM32 microcontroller (e.g., STM32F4 series)
- I2C-compatible slave device for testing

### Installation
1. Clone this repository:
   ```sh
  git clone https://github.com/your-repo/I2C1-Driver.git 
   ```
2. Include `i2c.h` and `i2c.c` in your STM32 project.

### Pin Configuration
I2C1 uses the following GPIO pins on the STM32 microcontroller:
- **PB6** - I2C1 SCL (Clock Line)
- **PB7** - I2C1 SDA (Data Line)

To change the default pin configuration, modify the GPIO initialization in `I2C1_Init()`:
```c
// Change PB6 and PB7 to alternative GPIO pins if needed
GPIOB->CRL &= ~((0xF << 24) | (0xF << 28));
GPIOB->CRL |= ((0xB << 24) | (0xB << 28));
```
Ensure that the chosen pins support I2C functionality in the STM32 datasheet.

### Usage
#### 1. Initialize I2C1
```c
I2C1_Init();
```

#### 2. Check if a device is ready
```c
uint8_t status = I2C1_IsDeviceReady(0x50);
```

#### 3. Transmit data in master mode
```c
uint8_t data[] = {0x10, 0x20};
I2C1_Master_Transmit(0x50, data, 2);
```

#### 4. Receive data in master mode
```c
uint8_t buffer[2];
I2C1_Master_Receive(0x50, buffer, 2);
```

#### 5. Write to memory
```c
uint8_t mem_data[] = {0xA5};
I2C1_Mem_Write(0x50, 0x01, mem_data, 1);
```

#### 6. Read from memory
```c
uint8_t mem_buffer[1];
I2C1_Mem_Read(0x50, 0x01, mem_buffer, 1);
```


