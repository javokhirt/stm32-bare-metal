#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

/* I2C1 master on PB8 (SCL) / PB9 (SDA), 100 kHz standard mode.
 * Register-address API: write the register, repeated START, then data.
 * n == 2 reads are not implemented (needs the POS bit, RM0383 §18.3.3). */

void i2c1_init(void);
void i2c1_read(uint8_t saddr, uint8_t maddr, uint16_t n, uint8_t *data);
void i2c1_write(uint8_t saddr, uint8_t maddr, uint16_t n, const uint8_t *data);

#endif /* I2C_H_ */
