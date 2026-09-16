#include "adc.h"
#include "stm32f4xx.h"

#define GPIOAEN       (1U<<0)
#define ADC1EN        (1U<<8)
#define CR2_ADCON     (1U<<0)
#define CR2_CONT      (1U<<1)
#define CR2_SWSTART   (1U<<30)
#define SR_EOC        (1U<<1)

void adc1_pa1_init(void) {
    RCC->AHB1ENR |= GPIOAEN;
    /* PA1 analog mode */
    GPIOA->MODER |= (1U<<2) | (1U<<3);

    RCC->APB2ENR |= ADC1EN;

    /* single-channel sequence: length 1, first (and only) conversion = ch 1 */
    ADC1->SQR3 = 1U;
    ADC1->SQR1 = 0U;

    ADC1->CR2 |= CR2_ADCON;
}

void adc1_start(void) {
    ADC1->CR2 |= CR2_SWSTART;
}

void adc1_start_continuous(void) {
    ADC1->CR2 |= CR2_CONT;
    ADC1->CR2 |= CR2_SWSTART;
}

uint16_t adc1_read(void) {
    while (!(ADC1->SR & SR_EOC)) {
    }
    return (uint16_t)ADC1->DR;   /* reading DR clears EOC */
}
