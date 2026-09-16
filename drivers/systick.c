#include "systick.h"
#include "stm32f4xx.h"

/* 1 ms at the 16 MHz processor clock: LOAD = f_clk / 1000 */
#define SYSTICK_LOAD_VAL     16000
#define CTRL_ENABLE          (1U<<0)
#define CTRL_CLKSOURCE       (1U<<2)   /* 1 = processor clock */
#define CTRL_COUNTFLAG       (1U<<16)  /* set on wrap to 0; cleared by reading CTRL */

void systick_delay_ms(int delay_ms) {
    SysTick->LOAD = SYSTICK_LOAD_VAL;
    SysTick->VAL  = 0;
    SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSOURCE;

    for (volatile int i = 0; i < delay_ms; i++) {
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {
        }
    }

    SysTick->CTRL = 0;
}
