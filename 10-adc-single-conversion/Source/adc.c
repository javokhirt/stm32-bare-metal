#include "stm32f411xe.h"
#include "adc.h"

#define GPIOAEN             (1U<<0)
#define ADCEN               (1U<<8)
#define ADC_CH1             (1U<<0)
#define ADC_LEN             (0x00)
#define CR2_ADCON           (1U<<0)
#define CR2_SWSTART         (1U<<30)
#define SR_EOC              (1U<<1)

void pa1_adc_init (void) {
    // ------------Configure the ADC GPIO pin------------------------------------
    // 1. enable clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;
    // 2. set the mode of the pin to analog
    GPIOA->MODER |= (1U<<3) | (1<<2);

    // ------------Configure the ADC------------------------------------
    // 3. enable clock access to ADC
    RCC->APB2ENR |= ADCEN;
    // configure the ADC parameters
    // conversion sequence start
    ADC1->SQR3 = ADC_CH1;
    // conversion sequence length
    ADC1->SQR1 = ADC_LEN;
    // enable ADC module
    ADC1->CR2 |= CR2_ADCON;

}

void start_conversion (void) {
    ADC1->CR2 |= CR2_SWSTART; // start conversion
}

uint32_t adc_read (void) {
    // wait the conversion to be complete
    while (!(ADC1->SR & SR_EOC)) {
        // do nothing
    }
    // read the converted result
    return ADC1->DR;
}