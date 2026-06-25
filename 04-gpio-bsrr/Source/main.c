#include "stm32f411xe.h"

#define GPIOAEN       (1U<<0)
#define GPIOCEN       (1U<<2)
#define PIN5          (1U<<5) 
#define led_pin       (PIN5)
#define PIN13         (1U<<13)
#define button_pin    (PIN13)

int main (void) {
    // 1. Enable clock access to GPIOA and GPIOC
    RCC->AHB1ENR |= GPIOAEN;
    RCC->AHB1ENR |= GPIOCEN;

    // 2. Set PA5 as an output pin
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &=~ (1U<<11); // set the bit 11 to 0 to set PA5 as an output pin

    // 3. Set PC13 as an input pin
    GPIOC->MODER &=~ (1U<<26);
    GPIOC->MODER &=~ (1U<<27);


    while (1) {
        // Idle: PC13 = HIGH (external pull-up). Pressed: PC13 = LOW (to GND).
        // Mask with & to isolate bit 13; never compare the whole IDR with ==.
        if ((GPIOC->IDR & button_pin) == 0) {
            GPIOA->BSRR = led_pin;   // pressed  -> LED ON
        } else {
            GPIOA->BSRR = (1U<<21);  // released -> LED OFF
        }
    }
}