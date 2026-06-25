#include "stm32f411xe.h"
#include "uart.h"
#include <stdio.h>
#include "systick.h"

// macrossssssssss

#define GPIOAEN          (1U<<0)
#define PIN5_ODR         (1U<<5) // ->setting the bit 5 to 1 to turn on the LED
#define LED_PIN          (PIN5_ODR)

// in this lesson, we're gonna learn how to use the systick timer to generate precise delay!!!


int main (void) {
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &=~ (1U<<11);

    usart2_TX_RX_init();
    setvbuf (stdout, NULL, _IONBF, 0);


    while (1) {
        GPIOA->ODR |= LED_PIN;
        systick_delay_ms(1000);
        GPIOA->ODR &=~ LED_PIN;
        systick_delay_ms(1000);
        printf("The LED Blinked Successfully\n\r");



    }
}

