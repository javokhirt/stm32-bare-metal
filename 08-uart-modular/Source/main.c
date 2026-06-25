#include <stdio.h> // for printf() and setvbuf() fucntions
#include "uart.h"

int main (void) {
    uart2_tx_init(); // initialize the UART2 module, set PA2 as the TX pin, and compute and set the baud rate!
    setvbuf(stdout, NULL, _IONBF, 0);
    
    while (1) {
        printf("Hello Mother Fucker!!! I fixed the bug by fucking it in the ass!!!\n\r");
        for (volatile int i=0; i<1000000; i++) {}
    }
}


