#include "stm32f411xe.h"
#include "adc.h"
#include "uart.h"
#include <stdio.h>


uint32_t adc_value;

int main (void) {
    pa1_adc_init ();

    usart2_TX_RX_init();
    setvbuf(stdout, NULL, _IONBF, 0);

    
    while (1) {
        start_conversion();
        adc_value = adc_read();
        printf("ADC Value: %d\n\r", (int) adc_value);
        for (volatile int i=0; i<1000000; i++) {}
    }
}

