#include "stm32f411xe.h"
#include <stdint.h>

#define GPIOAEN       (1U<<0)
#define USART2EN      (1U<<17)
#define USART2_TE     (1U<<3)
#define USART2_UE     (1U<<13)

#define SR_TXE        (1U<<7) // TXE bit is set when the transmit data register is empty!

#define SYS_FREQ      (16000000)
#define APB1_CLK      (SYS_FREQ) // the divider for APB1 is 1
#define BAUD_RATE     (115200)

static void set_baudrate (USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t BaudRate);
static uint16_t compute_baudrate (uint32_t PeriphCLK, uint32_t BaudRate);
void uart2_tx_init(void);
static void usart2_write(int chi);


int main (void) {
    uart2_tx_init(); // initialize the UART2 module, set PA2 as the TX pin, and compute and set the baud rate!
    
    while (1) {
    usart2_write('H');
    for (volatile int i=0; i<1000000; i++){

        }
    }
}

void uart2_tx_init(void) {
    // ------------Configuration of UART GPIO Pin
    // 1. Enable clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;
    // 2. Set PA2 to alternate function mode
    GPIOA->MODER |= (1U<<5);
    GPIOA->MODER &=~ (1U<<4);
    // 3. Set PA2 alternate function type to UART_TX (AF07)
    GPIOA->AFR[0] |= (1U<<8);
    GPIOA->AFR[0] |= (1U<<9);
    GPIOA->AFR[0] |= (1U<<10);
    GPIOA->AFR[0] &=~ (1U<<11);


    //-------------Configuration of UART Module
    // 1. Enable clock access to USART2
    RCC->APB1ENR |= USART2EN;
    // 2. Configure the baud rate
    set_baudrate (USART2, APB1_CLK, BAUD_RATE);
    // 3. Configure the transfer direction (TX)
    USART2->CR1 = USART2_TE; // intentioally clearning the register and setting only bit 3 to 1! 
    // 4. Enable the UART module
    USART2->CR1 |= USART2_UE;   //UE bit to 1!  
}

static void usart2_write(int ch) {
    // 1. make sure the transmit data register empty!
    while (!(USART2->SR & SR_TXE))  {
        // do nothing!
    }
    // 2. write the data to the transmit data register!
    USART2->DR = (ch & 0xFF);
}

static void set_baudrate (USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t BaudRate) {
    USARTx->BRR = compute_baudrate(PeriphCLK, BaudRate);
    // this assigns the computed value to the BRR register!
}

static uint16_t compute_baudrate (uint32_t PeriphCLK, uint32_t BaudRate) {
    return((PeriphCLK + (BaudRate/2U)) / BaudRate);
    // this value is gonna be written to our UART register! 
} 