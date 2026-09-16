#include "i2c.h"
#include "systick.h"
#include "uart.h"
#include <stdio.h>

/* Reads the WHO_AM_I register of an MPU6050 once a second.
 * Any register-based device works — change the address and register.
 * Expects 0x68 back; a hang means nothing ACKed on the bus. */

#define MPU6050_ADDR       0x68U
#define MPU6050_WHO_AM_I   0x75U

int main(void) {
    uart2_init();
    setvbuf(stdout, NULL, _IONBF, 0);
    i2c1_init();

    while (1) {
        uint8_t id = 0;
        i2c1_read(MPU6050_ADDR, MPU6050_WHO_AM_I, 1, &id);
        printf("WHO_AM_I: 0x%02X\r\n", id);
        systick_delay_ms(1000);
    }
}
