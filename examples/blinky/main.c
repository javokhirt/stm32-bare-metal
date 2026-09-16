#include "gpio.h"
#include "systick.h"

int main(void) {
    led_init();

    while (1) {
        led_toggle();
        systick_delay_ms(500);
    }
}
