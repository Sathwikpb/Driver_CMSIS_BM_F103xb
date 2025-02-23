# STM32F103 UART Communication

## Overview
This project initializes and uses UART2 on the STM32F103 microcontroller to send a string via the serial interface. The implementation directly manipulates hardware registers for low-level control over UART communication.

## Hardware Configuration
- **Microcontroller**: STM32F103RB
- **Baud Rate**: 115200
- **UART TX Pin**: PA2

## Code Breakdown

### 1. **Enabling Clocks**
The following lines enable the clock for GPIOA (where UART2 TX is mapped) and USART2:
```c
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Enable GPIOA clock
RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock
```

### 2. **Configuring GPIOA for UART2 TX (PA2)**
PA2 needs to be set as an alternate function push-pull for UART transmission:
```c
GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
GPIOA->CRL |= (1U << 9);  // CNF2[1] = 1 (Alternate Function Push-Pull)
GPIOA->CRL &= ~(1U << 8); // CNF2[0] = 0
GPIOA->CRL |= (1U << 11); // MODE2[1] = 1 (Output Mode, 10 MHz)
GPIOA->CRL &= ~(1U << 10); // MODE2[0] = 0
```

### 3. **Setting UART Baud Rate**
The baud rate is configured as:
```c
USART2->BRR = (uint32_t)(8000000 / 115200);
```
- The system clock (PCLK1) is 8 MHz.
- The baud rate divisor is computed as `8,000,000 / 115200`.

### 4. **Enabling UART Transmission**
The USART2 peripheral is enabled with the following settings:
```c
USART2->CR1 |= (USART_CR1_TE | USART_CR1_UE);
```
- `USART_CR1_TE`: Enable transmitter.
- `USART_CR1_UE`: Enable USART.

### 5. **UART Write Function**
A helper function is implemented to send a single character over UART:
```c
static void uart2_write(int ch) {
    while (!(USART2->SR & USART_SR_TXE)) {} // Wait until TX buffer is empty
    USART2->DR = (ch & 0xFF); // Send character
}
```
- `USART_SR_TXE`: Checks if the transmit data register is empty.
- `USART2->DR`: Sends the byte.

### 6. **Redirecting `printf()` to UART**
To use `printf()`, the function `__io_putchar()` is implemented:
```c
int __io_putchar(int ch) {
    uart2_write(ch);
    return ch;
}
```
This allows `printf()` to send data via UART automatically.

### 7. **Main Function Execution**
```c
int main(void) {
    UART2_Init();
    while (1) {
        printf("How are youuuu \r\n");
    }
}
```
- Calls `UART2_Init()` to set up UART.
- In an infinite loop, prints "How are youuuu" continuously over UART.

## Summary of Registers Used
| Register        | Purpose |
|----------------|---------|
| `RCC->APB2ENR` | Enables GPIOA clock |
| `RCC->APB1ENR` | Enables USART2 clock |
| `GPIOA->CRL`   | Configures PA2 for UART TX (Alternate Function Push-Pull) |
| `USART2->BRR`  | Sets UART baud rate |
| `USART2->CR1`  | Enables UART and TX functionality |
| `USART2->SR`   | Checks if transmit buffer is empty |
| `USART2->DR`   | Loads data to send |

## How to Use
1. Flash this firmware to an STM32F103-based board.
2. Open a serial monitor (Baud rate: **115200**, 8N1 settings).
3. Observe the output "How are youuuu" repeating in the serial monitor.

## Future Improvements
- Implement UART RX to receive data.
- Use DMA for efficient data transfer.
- Add interrupt-driven UART handling.



