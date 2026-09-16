#include "i2c.h"
#include "stm32f4xx.h"

#define GPIOBEN         (1U<<1)
#define I2C1EN          (1U<<21)

#define CR1_PE          (1U<<0)
#define CR1_START       (1U<<8)
#define CR1_STOP        (1U<<9)
#define CR1_ACK         (1U<<10)
#define CR1_SWRST       (1U<<15)

#define SR1_SB          (1U<<0)
#define SR1_ADDR        (1U<<1)
#define SR1_BTF         (1U<<2)
#define SR1_RXNE        (1U<<6)
#define SR1_TXE         (1U<<7)
#define SR2_BUSY        (1U<<1)

void i2c1_init(void) {
    RCC->AHB1ENR |= GPIOBEN;

    /* PB8 = SCL, PB9 = SDA, AF4, open-drain with pull-ups */
    GPIOB->MODER &=~ (1U<<16);
    GPIOB->MODER |=  (1U<<17);
    GPIOB->MODER &=~ (1U<<18);
    GPIOB->MODER |=  (1U<<19);
    GPIOB->AFR[1] |= (1U<<2);
    GPIOB->AFR[1] |= (1U<<6);

    GPIOB->OTYPER |= (1U<<8) | (1U<<9);
    GPIOB->PUPDR  |= (1U<<16) | (1U<<18);

    RCC->APB1ENR |= I2C1EN;

    I2C1->CR1 |= CR1_SWRST;
    I2C1->CR1 &=~ CR1_SWRST;

    /* CR2.FREQ = APB1 clock in MHz (16 MHz HSI) */
    I2C1->CR2 |= (16U<<0);

    /* CCR = 80 -> 100 kHz standard mode: Thigh = Tlow = 80 * T_PCLK1 */
    I2C1->CCR = 80U;

    /* TRISE = (max SCL rise time / T_PCLK1) + 1 = 1000 ns / 62.5 ns + 1 */
    I2C1->TRISE = 17U;

    I2C1->CR1 |= CR1_PE;
}

void i2c1_read(uint8_t saddr, uint8_t maddr, uint16_t n, uint8_t *data) {
    volatile uint32_t tmp;

    /* n == 2 needs the POS bit and a different sequence — not implemented. */
    if (n == 0U || n == 2U) {
        return;
    }

    while (I2C1->SR2 & SR2_BUSY) {
    }

    /* write phase: select the register */
    I2C1->CR1 |= CR1_START;
    while (!(I2C1->SR1 & SR1_SB)) {
    }
    I2C1->DR = (uint8_t)(saddr << 1);
    while (!(I2C1->SR1 & SR1_ADDR)) {
    }
    tmp = I2C1->SR2;   /* reading SR1 then SR2 clears ADDR */

    I2C1->DR = maddr;
    while (!(I2C1->SR1 & SR1_TXE)) {
    }

    /* repeated START, read phase */
    I2C1->CR1 |= CR1_START;
    while (!(I2C1->SR1 & SR1_SB)) {
    }
    I2C1->DR = (uint8_t)((saddr << 1) | 1U);
    while (!(I2C1->SR1 & SR1_ADDR)) {
    }

    if (n == 1U) {
        /* single byte: ACK must already be off when ADDR is cleared,
         * because the byte starts arriving the moment it is */
        I2C1->CR1 &=~ CR1_ACK;
        tmp = I2C1->SR2;
        I2C1->CR1 |= CR1_STOP;
        while (!(I2C1->SR1 & SR1_RXNE)) {
        }
        *data = I2C1->DR;
        return;
    }

    I2C1->CR1 |= CR1_ACK;
    tmp = I2C1->SR2;
    (void)tmp;

    while (n > 3U) {
        while (!(I2C1->SR1 & SR1_RXNE)) {
        }
        *data++ = I2C1->DR;
        n--;
    }

    /* Last three bytes. Clearing ACK inside a per-byte loop races the wire:
     * byte N is already arriving while the loop decides. BTF means DR and the
     * shift register are both full and SCL is stretched, so ACK is cleared
     * while nothing is moving (RM0383 §18.3.3 master receiver). */
    while (!(I2C1->SR1 & SR1_BTF)) {
    }
    I2C1->CR1 &=~ CR1_ACK;
    *data++ = I2C1->DR;        /* releasing DR restarts the clock */
    I2C1->CR1 |= CR1_STOP;
    *data++ = I2C1->DR;
    while (!(I2C1->SR1 & SR1_RXNE)) {
    }
    *data = I2C1->DR;
}

void i2c1_write(uint8_t saddr, uint8_t maddr, uint16_t n, const uint8_t *data) {
    volatile uint32_t tmp;

    while (I2C1->SR2 & SR2_BUSY) {
    }

    I2C1->CR1 |= CR1_START;
    while (!(I2C1->SR1 & SR1_SB)) {
    }
    I2C1->DR = (uint8_t)(saddr << 1);
    while (!(I2C1->SR1 & SR1_ADDR)) {
    }
    tmp = I2C1->SR2;
    (void)tmp;

    I2C1->DR = maddr;

    for (uint16_t i = 0; i < n; i++) {
        while (!(I2C1->SR1 & SR1_TXE)) {
        }
        I2C1->DR = *data++;
    }

    /* BTF: the last byte has left DR and is on the wire — then STOP */
    while (!(I2C1->SR1 & SR1_BTF)) {
    }
    I2C1->CR1 |= CR1_STOP;
}
