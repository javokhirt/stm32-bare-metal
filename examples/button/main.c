#include "gpio.h"

int main(void) {
    led_init();
    button_init();

    while (1) {
        if (button_pressed()) {
            led_on();
        } else {
            led_off();
        }
    }
}
