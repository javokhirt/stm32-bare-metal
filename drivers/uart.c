#include "uart.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include <sys/types.h>   /* ssize_t for the _write prototype */

#define GPIOAEN     (1U<<0)
#define USART2EN    (1U<<17)

#define CR1_RE      (1U<<2)
#define CR1_TE      (1U<<3)
#define CR1_UE      (1U<<13)
#define SR_RXNE     (1U<<5)
#define SR_TXE      (1U<<7)

#define APB1_CLK    (16000000U)  /* HSI, APB1 prescaler = 1 */
#define BAUD_RATE   (115200U)

static void usart2_write(int ch);

void uart2_init(void) {
    RCC->AHB1ENR |= GPIOAEN;

    /* PA2 = USART2_TX, PA3 = USART2_RX, both AF7 */
    GPIOA->MODER &=~ (1U<<4);
    GPIOA->MODER |=  (1U<<5);
    GPIOA->MODER &=~ (1U<<6);
    GPIOA->MODER |=  (1U<<7);

    GPIOA->AFR[0] |=  (1U<<8);
    GPIOA->AFR[0] |=  (1U<<9);
    GPIOA->AFR[0] |=  (1U<<10);
    GPIOA->AFR[0] &=~ (1U<<11);
    GPIOA->AFR[0] |=  (1U<<12);
    GPIOA->AFR[0] |=  (1U<<13);
    GPIOA->AFR[0] |=  (1U<<14);
    GPIOA->AFR[0] &=~ (1U<<15);

    RCC->APB1ENR |= USART2EN;

    /* BRR = f_clk / baud, rounded to nearest */
    USART2->BRR = (uint16_t)((APB1_CLK + (BAUD_RATE / 2U)) / BAUD_RATE);

    USART2->CR1 = CR1_TE | CR1_RE;
    USART2->CR1 |= CR1_UE;
}

char uart2_read(void) {
    while (!(USART2->SR & SR_RXNE)) {
    }
    return (char)(USART2->DR & 0xFF);
}

static void usart2_write(int ch) {
    while (!(USART2->SR & SR_TXE)) {
    }
    USART2->DR = (ch & 0xFF);
}

/* newlib lands here at the bottom of every printf(); stream the bytes
 * out of USART2 instead of the libnosys stub throwing them away. */
ssize_t _write(int file, const char *ptr, ssize_t len) {
    (void)file;
    for (ssize_t i = 0; i < len; i++) {
        usart2_write((unsigned char)ptr[i]);
    }
    return len;
}
