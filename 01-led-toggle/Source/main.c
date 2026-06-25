#include <stdint.h>


// where is the led connected??
// Port: A
// Pin: 5

#define peripheral_base       	(0x40000000UL)

#define AHB1_periph_offset    	(0x00020000UL) //BUS
#define AHB1_periph_base      	(peripheral_base + AHB1_periph_offset) // AHB1 bus starting address

#define GPIOA_offset            (0x00000000UL)
#define GPIOA_base    			(AHB1_periph_base + GPIOA_offset) // GPIO Port A starting address

#define RCC_offset              (0x00003800UL)
#define RCC_base				(AHB1_periph_base + RCC_offset) // RCC starting address

#define RCC_AHB1EN_R_offset 	(0x30UL)
#define RCC_AHB1EN_R            (*(volatile unsigned int *) (RCC_base + RCC_AHB1EN_R_offset)) // set the bit 0 of this register to 1 to enable clock to GPIOA
#define GPIOAEN                 (1U<<0)

#define GPIOA_MODER_R_offset    (0x00UL)
#define GPIOA_MODER_R           (*(volatile unsigned int *) (GPIOA_base + GPIOA_MODER_R_offset)) // set the bit 10 of this register to 1 to set PA5 as an output pin
// The reset value of this register is 0xA8000000
#define PIN5_MODER_output       (1U<<10)

#define GPIOA_ODR_R_offset      (0x14UL)
#define GPIOA_ODR_R             (*(volatile unsigned int *) (GPIOA_base + GPIOA_ODR_R_offset) ) // (1U<<5) -> to set bit 5 to 1 to turn on the LED

#define PIN5_ODR           (1U<<5) // ->setting the bit 5 to 1 to turn on the LED
#define LED                 (PIN5_ODR)

typedef struct {
    volatile uint32_t MODER;



}GPIO_TypeDef;




int main () {
    //1. Enable clock access to GPIOA
    RCC_AHB1EN_R |= GPIOAEN; // |= means OR Operator
    //2. Set PA5 as an output pin
    GPIOA_MODER_R |= PIN5_MODER_output;
    GPIOA_MODER_R &=~ (0U<<11);
    while (1) {
        //3. Set Pin 5 high
        // GPIOA_ODR_R |= LED;
        GPIOA_ODR_R ^= LED; //-> it's a toggle operator!!!
        for (int i = 0; i <3000000; i++) { 
        }
    }



}















