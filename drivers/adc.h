#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

/* ADC1 on PA1 (channel 1), 12-bit, software-triggered. */

void adc1_pa1_init(void);
void adc1_start(void);             /* one conversion */
void adc1_start_continuous(void);  /* free-running */
uint16_t adc1_read(void);          /* blocks on EOC */

#endif /* ADC_H_ */
