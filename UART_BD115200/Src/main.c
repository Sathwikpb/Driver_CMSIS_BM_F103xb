


#include "stm32f103xb.h"
#include <stdio.h>
#include <string.h>

#define UART_BAUDRATE 115200





static void uart2_write(int ch);


int __io_putchar(int ch){
	uart2_write(ch);
	return ch;

}


void UART2_Init(void) {
    // Enable GPIOA and USART2 clocks
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;


    // Configure PA2 as USART2_TX
    GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
    GPIOA->CRL |= (1U<<9);
    GPIOA->CRL &=~ (1U<<8);

    GPIOA->CRL |= (1U<<11);
    GPIOA->CRL &=~ (1U<<10);

   AFIO->MAPR &=~AFIO_MAPR_USART2_REMAP;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = (uint32_t)(8000000 / 115200);
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_UE);
}



static void uart2_write(int ch)
{
	while(!(USART2->SR & USART_SR_TXE)){}

	USART2->DR =(ch & 0xFF);
}



int main(void) {

    UART2_Init();



    while (1) {
    	 printf("How are youuuu \r\n");
    }
}
