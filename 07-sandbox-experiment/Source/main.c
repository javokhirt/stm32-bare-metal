// ---------------- THE PROJECT IS ON HOLD FOR NOW!!!


#include "stm32f411xe.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h> // for ssize_t used in the _write prototype

#define SYS_FREQ      (16000000)
#define APB1_CLK      (SYS_FREQ)
#define BAUD_RATE     (115200)


#define GPIOAEN       (1U<<0)
#define USART2EN      (1U<<17)

#define USART2_RE     (1U<<2)
#define USART2_TE     (1U<<3)
#define USART2_UE     (1U<<13)

#define SR_TXE    (1U<<7)



uint16_t compute_baudrate (uint32_t PeriphClock, uint32_t BaudRate);
void set_baudrate (USART_TypeDef *USARTx, uint32_t PeriphClock, uint32_t BaudRate);
void usart2_TX_RX_init(void);
static void usart2_write (int ch);

int main (void) {

    usart2_TX_RX_init();
    while (1) {
        printf("Hello you broke ASS!!! \n\r");

    }
}

ssize_t _write (int file, const char *ptr, ssize_t len) {
    (void)file; // the signature is accepted but we never use it! For warning supression!
    for (ssize_t i=0; i<len; i++) {
        usart2_write(ptr[i]);
    }
    return len;
}


static void usart2_write (int ch) {
    while (!(USART2->SR & SR_TXE)) {

        // do nothing!
    }
    USART2->DR = (ch & 0xFF);
}

void usart2_TX_RX_init(void) {
    // ------------Configuration of UART GPIO Pin
    // 1. Enable clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;
    // 2. Set PA2 and PA3 to alternate function mode
    GPIOA->MODER &=~ (1U<<4); // PA2
    GPIOA->MODER |=  (1U<<5); // PA2

    GPIOA->MODER &=~ (1U<<6); // PA3
    GPIOA->MODER |=  (1U<<7); // PA3
    
    // 3. Set PA2 and PA3 to alternate function type to UART_TX and UART_RX (AF07)
    // Setting PA2 alternate function type to UART_TX (AF07)
    GPIOA->AFR[0] |= (1U<<8);
    GPIOA->AFR[0] |= (1U<<9);
    GPIOA->AFR[0] |= (1U<<10);
    GPIOA->AFR[0] &=~ (1U<<11);
    // Setting PA3 alternate function type to UART_RX (AF07)
    GPIOA->AFR[0] |= (1U<<12);
    GPIOA->AFR[0] |= (1U<<13);
    GPIOA->AFR[0] |= (1U<<14);
    GPIOA->AFR[0] &=~ (1U<<15);

    // -------------Configure the UART Module
    // 1. Enable clock access to USART2 via APB1ENR
    RCC->APB1ENR |= USART2EN;
    // 2. Configure the baud rate
    set_baudrate (USART2, APB1_CLK, BAUD_RATE);
    // 3. Configure the transfer direction (TX and RX)
    USART2->CR1 |= USART2_RE;
    USART2->CR1 |= USART2_TE;
    // 4. Enable the UART module
    USART2->CR1 |= USART2_UE;
}


void set_baudrate (USART_TypeDef *USARTx, uint32_t PeriphClock, uint32_t BaudRate) {
    USARTx->BRR = compute_baudrate(PeriphClock, BaudRate); // this assigns the computed value to the BRR register!
}

uint16_t compute_baudrate (uint32_t PeriphClock, uint32_t BaudRate) {
    return ((PeriphClock + (BaudRate/2U)) / BaudRate);
}





