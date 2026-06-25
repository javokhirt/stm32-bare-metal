#include "stm32f411xe.h"
#include "tim.h"

// we're gonna write a driver for timer 2 that will generate a timeout each second!!!

#define TIM2EN       (1U<<0)  // enable clock access to TIM2, bit 0
#define CR1_EN        (1U<<0) // enable timer


void tim2_1hz_init (void) {

    // enable clock access to TIM2
    RCC->APB1ENR |= TIM2EN;
    // set prescaler value
    TIM2->PSC = 16000 - 1; // 1000 ticks per second!!!
    // set auto-reload value
    TIM2->ARR = 2000- 1; // results in a 2Hz timeout!!!
    // clear the counter
    TIM2->CNT = 0;
    // enable the timer
    TIM2->CR1 |= CR1_EN;

    TIM2->SR &=~ SR_UIF;  // clear the update interrupt flag
}