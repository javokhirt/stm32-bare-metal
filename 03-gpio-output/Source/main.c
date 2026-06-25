#include "stm32f411xe.h"

#define GPIOAEN       (1U<<0)
#define PIN5          (1U<<5) 
#define led_pin       (PIN5)

int main (void) {
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &=~ (1U<<11);


    while (1) {
        GPIOA->ODR ^= led_pin;
        for (int i=0; i<1000000; i++) {


        }


    }



}