#include "gpio.h"
#include "stm32f4xx.h"

#define GPIOAEN   (1U<<0)
#define GPIOCEN   (1U<<2)
#define LED_PIN   (1U<<5)   /* PA5 */
#define BTN_PIN   (1U<<13)  /* PC13 */

void led_init(void) {
    RCC->AHB1ENR |= GPIOAEN;
    /* PA5 output */
    GPIOA->MODER |=  (1U<<10);
    GPIOA->MODER &=~ (1U<<11);
}

/* Set/reset through BSRR: single write, no read-modify-write to race against. */
void led_on(void) {
    GPIOA->BSRR = LED_PIN;
}

void led_off(void) {
    GPIOA->BSRR = (LED_PIN << 16);
}

void led_toggle(void) {
    GPIOA->ODR ^= LED_PIN;
}

void button_init(void) {
    RCC->AHB1ENR |= GPIOCEN;
    /* PC13 input; the board provides an external pull-up */
    GPIOC->MODER &=~ (1U<<26);
    GPIOC->MODER &=~ (1U<<27);
}

/* Idle high, pressed low. */
bool button_pressed(void) {
    return (GPIOC->IDR & BTN_PIN) == 0;
}
