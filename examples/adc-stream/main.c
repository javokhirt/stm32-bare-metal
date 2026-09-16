#include "adc.h"
#include "uart.h"
#include <stdio.h>

/* Streams free-running conversions of PA1 over UART. */

int main(void) {
    uart2_init();
    setvbuf(stdout, NULL, _IONBF, 0);

    adc1_pa1_init();
    adc1_start_continuous();

    while (1) {
        printf("PA1: %u\r\n", (unsigned)adc1_read());
    }
}
