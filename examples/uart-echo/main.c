#include "gpio.h"
#include "uart.h"
#include <stdio.h>

/* Echoes every byte back; '1' turns the LED on, anything else turns it off. */

int main(void) {
    uart2_init();
    setvbuf(stdout, NULL, _IONBF, 0);
    led_init();

    printf("uart-echo ready\r\n");

    while (1) {
        char c = uart2_read();
        printf("%c", c);

        if (c == '1') {
            led_on();
        } else {
            led_off();
        }
    }
}
