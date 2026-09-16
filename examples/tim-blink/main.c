#include "gpio.h"
#include "tim.h"
#include "uart.h"
#include <stdio.h>

/* LED paced by TIM2 update events instead of a busy-wait delay. */

int main(void) {
    uart2_init();
    setvbuf(stdout, NULL, _IONBF, 0);

    led_init();
    tim2_init_1hz();

    while (1) {
        tim2_wait_update();
        led_toggle();
        printf("tick\r\n");
    }
}
