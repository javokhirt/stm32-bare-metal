#ifndef UART_H_
#define UART_H_

/* USART2 on PA2 (TX) / PA3 (RX), 115200 8N1, driven off the 16 MHz HSI.
 * On a Nucleo these pins route to the ST-Link virtual COM port.
 * printf() is retargeted here via _write(). */

void uart2_init(void);
char uart2_read(void);   /* blocking */

#endif /* UART_H_ */
