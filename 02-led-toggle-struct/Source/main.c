// where is the led connected??
// Port: A
// Pin: 5

#include <stdint.h>
#define peripheral_base       	(0x40000000UL)

#define AHB1_periph_offset    	(0x00020000UL) //BUS
#define AHB1_periph_base      	(peripheral_base + AHB1_periph_offset) // AHB1 bus starting address

#define GPIOA_offset            (0x00000000UL)
#define GPIOA_base    			(AHB1_periph_base + GPIOA_offset) // GPIO Port A starting address

#define RCC_offset              (0x00003800UL)
#define RCC_base				(AHB1_periph_base + RCC_offset) // RCC starting address


#define GPIOAEN                 (1U<<0)
#define PIN5_ODR                (1U<<5) // ->setting the bit 5 to 1 to turn on the LED
#define LED                     (PIN5_ODR)

typedef struct {
    volatile uint32_t Dummy[12]; 
    volatile uint32_t AHB1ENR;
}RCC_TypeDef;

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t Dummy[4];
    volatile uint32_t ODR;
}GPIOA_TypeDef;

#define RCC          ((RCC_TypeDef *) (RCC_base))
#define GPIOA        ((GPIOA_TypeDef *) (GPIOA_base))

int main (void) {
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &=~ (1U<<11);
    
    while (1) {
        GPIOA->ODR ^= LED;
        for (int i=0; i<1000000; i++) {
            
        }
    }
}