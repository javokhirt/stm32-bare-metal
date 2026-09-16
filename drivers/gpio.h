#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>

/* Nucleo-F411RE board pins: LD2 on PA5, B1 user button on PC13. */

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

void button_init(void);
bool button_pressed(void);

#endif /* GPIO_H_ */
