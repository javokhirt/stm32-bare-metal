#include "stm32f411xe.h"
#include <stdint.h>
#include <stdio.h> // for printf() and setvbuf() fucntions
#include "uart.h"

#define GPIOAEN       (1U<<0)
#define PA5           (1U<<5)

char key;

int main (void) {
    usart2_TX_RX_init(); // initialize the UART2 module, set PA2 as the TX pin, and compute and set the baud rate!
    setvbuf(stdout, NULL, _IONBF, 0);
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |=  (1U<<10);
    GPIOA->MODER &=~ (1U<<11);
    
    
    while (1) {
        key = usart2_read();
        if (key == '1') {
            GPIOA->ODR |= PA5;

        }else {
            GPIOA->ODR &=~ PA5;
        }
    }
}


