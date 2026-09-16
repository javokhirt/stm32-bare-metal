#ifndef TIM_H_
#define TIM_H_

/* TIM2 as a 1 Hz timebase off the 16 MHz HSI. */

void tim2_init_1hz(void);
void tim2_wait_update(void);   /* block until the next update event */

#endif /* TIM_H_ */
