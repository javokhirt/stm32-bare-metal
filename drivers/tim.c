#include "tim.h"
#include "stm32f4xx.h"

#define TIM2EN     (1U<<0)
#define CR1_CEN    (1U<<0)
#define SR_UIF     (1U<<0)

void tim2_init_1hz(void) {
    RCC->APB1ENR |= TIM2EN;

    /* 16 MHz / 16000 = 1 kHz counter clock; 1000 ticks per update = 1 Hz */
    TIM2->PSC = 16000 - 1;
    TIM2->ARR = 1000 - 1;
    TIM2->CNT = 0;

    TIM2->CR1 |= CR1_CEN;
    TIM2->SR &=~ SR_UIF;
}

void tim2_wait_update(void) {
    while ((TIM2->SR & SR_UIF) == 0) {
    }
    TIM2->SR &=~ SR_UIF;
}
