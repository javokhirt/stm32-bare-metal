/*
 * STM32F446RE Register Definitions
 * Bare-metal register map for the STM32F446RE (ARM Cortex-M4)
 *
 * This header provides direct register access without HAL/CMSIS dependencies.
 * All addresses and bit definitions are from the STM32F446xx Reference Manual (RM0390).
 */

#ifndef STM32F446RE_H
#define STM32F446RE_H

#include <stdint.h>

/* ========================================================================= */
/*                          Memory Map                                       */
/* ========================================================================= */

#define FLASH_BASE          0x08000000UL
#define SRAM_BASE           0x20000000UL
#define PERIPH_BASE         0x40000000UL

#define APB1_BASE           PERIPH_BASE
#define APB2_BASE           (PERIPH_BASE + 0x00010000UL)
#define AHB1_BASE           (PERIPH_BASE + 0x00020000UL)
#define AHB2_BASE           (PERIPH_BASE + 0x10000000UL)

/* ARM Cortex-M4 Core Peripherals */
#define SCS_BASE            0xE000E000UL
#define SYSTICK_BASE        0xE000E010UL
#define NVIC_BASE           0xE000E100UL
#define SCB_BASE            0xE000ED00UL
#define FPU_BASE            0xE000EF30UL

/* ========================================================================= */
/*                    Peripheral Register Structures                         */
/* ========================================================================= */

/* ---- GPIO ---- */
typedef struct {
    volatile uint32_t MODER;        /* 0x00: Mode register */
    volatile uint32_t OTYPER;       /* 0x04: Output type register */
    volatile uint32_t OSPEEDR;      /* 0x08: Output speed register */
    volatile uint32_t PUPDR;        /* 0x0C: Pull-up/pull-down register */
    volatile uint32_t IDR;          /* 0x10: Input data register */
    volatile uint32_t ODR;          /* 0x14: Output data register */
    volatile uint32_t BSRR;        /* 0x18: Bit set/reset register */
    volatile uint32_t LCKR;        /* 0x1C: Configuration lock register */
    volatile uint32_t AFR[2];      /* 0x20-0x24: Alternate function registers (L/H) */
} GPIO_TypeDef;

/* ---- RCC ---- */
typedef struct {
    volatile uint32_t CR;           /* 0x00: Clock control register */
    volatile uint32_t PLLCFGR;     /* 0x04: PLL configuration register */
    volatile uint32_t CFGR;        /* 0x08: Clock configuration register */
    volatile uint32_t CIR;         /* 0x0C: Clock interrupt register */
    volatile uint32_t AHB1RSTR;    /* 0x10: AHB1 peripheral reset register */
    volatile uint32_t AHB2RSTR;    /* 0x14: AHB2 peripheral reset register */
    volatile uint32_t AHB3RSTR;    /* 0x18: AHB3 peripheral reset register */
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;    /* 0x20: APB1 peripheral reset register */
    volatile uint32_t APB2RSTR;    /* 0x24: APB2 peripheral reset register */
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;     /* 0x30: AHB1 peripheral clock enable register */
    volatile uint32_t AHB2ENR;     /* 0x34: AHB2 peripheral clock enable register */
    volatile uint32_t AHB3ENR;     /* 0x38: AHB3 peripheral clock enable register */
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;     /* 0x40: APB1 peripheral clock enable register */
    volatile uint32_t APB2ENR;     /* 0x44: APB2 peripheral clock enable register */
    uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;   /* 0x50 */
    volatile uint32_t AHB2LPENR;   /* 0x54 */
    volatile uint32_t AHB3LPENR;   /* 0x58 */
    uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;   /* 0x60 */
    volatile uint32_t APB2LPENR;   /* 0x64 */
    uint32_t RESERVED5[2];
    volatile uint32_t BDCR;        /* 0x70: Backup domain control register */
    volatile uint32_t CSR;         /* 0x74: Clock control & status register */
    uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;       /* 0x80: Spread spectrum clock generation register */
    volatile uint32_t PLLI2SCFGR;  /* 0x84 */
    volatile uint32_t PLLSAICFGR;  /* 0x88 */
    volatile uint32_t DCKCFGR;     /* 0x8C */
    volatile uint32_t CKGATENR;    /* 0x90 */
    volatile uint32_t DCKCFGR2;    /* 0x94 */
} RCC_TypeDef;

/* ---- USART ---- */
typedef struct {
    volatile uint32_t SR;          /* 0x00: Status register */
    volatile uint32_t DR;          /* 0x04: Data register */
    volatile uint32_t BRR;         /* 0x08: Baud rate register */
    volatile uint32_t CR1;         /* 0x0C: Control register 1 */
    volatile uint32_t CR2;         /* 0x10: Control register 2 */
    volatile uint32_t CR3;         /* 0x14: Control register 3 */
    volatile uint32_t GTPR;        /* 0x18: Guard time and prescaler register */
} USART_TypeDef;

/* ---- SPI ---- */
typedef struct {
    volatile uint32_t CR1;         /* 0x00: Control register 1 */
    volatile uint32_t CR2;         /* 0x04: Control register 2 */
    volatile uint32_t SR;          /* 0x08: Status register */
    volatile uint32_t DR;          /* 0x0C: Data register */
    volatile uint32_t CRCPR;       /* 0x10: CRC polynomial register */
    volatile uint32_t RXCRCR;      /* 0x14: RX CRC register */
    volatile uint32_t TXCRCR;      /* 0x18: TX CRC register */
    volatile uint32_t I2SCFGR;     /* 0x1C: I2S configuration register */
    volatile uint32_t I2SPR;       /* 0x20: I2S prescaler register */
} SPI_TypeDef;

/* ---- I2C ---- */
typedef struct {
    volatile uint32_t CR1;         /* 0x00: Control register 1 */
    volatile uint32_t CR2;         /* 0x04: Control register 2 */
    volatile uint32_t OAR1;        /* 0x08: Own address register 1 */
    volatile uint32_t OAR2;        /* 0x0C: Own address register 2 */
    volatile uint32_t DR;          /* 0x10: Data register */
    volatile uint32_t SR1;         /* 0x14: Status register 1 */
    volatile uint32_t SR2;         /* 0x18: Status register 2 */
    volatile uint32_t CCR;         /* 0x1C: Clock control register */
    volatile uint32_t TRISE;       /* 0x20: TRISE register */
    volatile uint32_t FLTR;        /* 0x24: FLTR register */
} I2C_TypeDef;

/* ---- TIM (General Purpose Timer) ---- */
typedef struct {
    volatile uint32_t CR1;         /* 0x00: Control register 1 */
    volatile uint32_t CR2;         /* 0x04: Control register 2 */
    volatile uint32_t SMCR;        /* 0x08: Slave mode control register */
    volatile uint32_t DIER;        /* 0x0C: DMA/Interrupt enable register */
    volatile uint32_t SR;          /* 0x10: Status register */
    volatile uint32_t EGR;         /* 0x14: Event generation register */
    volatile uint32_t CCMR1;       /* 0x18: Capture/compare mode register 1 */
    volatile uint32_t CCMR2;       /* 0x1C: Capture/compare mode register 2 */
    volatile uint32_t CCER;        /* 0x20: Capture/compare enable register */
    volatile uint32_t CNT;         /* 0x24: Counter */
    volatile uint32_t PSC;         /* 0x28: Prescaler */
    volatile uint32_t ARR;         /* 0x2C: Auto-reload register */
    volatile uint32_t RCR;         /* 0x30: Repetition counter register */
    volatile uint32_t CCR1;        /* 0x34: Capture/compare register 1 */
    volatile uint32_t CCR2;        /* 0x38: Capture/compare register 2 */
    volatile uint32_t CCR3;        /* 0x3C: Capture/compare register 3 */
    volatile uint32_t CCR4;        /* 0x40: Capture/compare register 4 */
    volatile uint32_t BDTR;        /* 0x44: Break and dead-time register */
    volatile uint32_t DCR;         /* 0x48: DMA control register */
    volatile uint32_t DMAR;        /* 0x4C: DMA address for full transfer */
} TIM_TypeDef;

/* ---- DMA Stream ---- */
typedef struct {
    volatile uint32_t CR;          /* 0x00: Stream configuration register */
    volatile uint32_t NDTR;        /* 0x04: Number of data register */
    volatile uint32_t PAR;         /* 0x08: Peripheral address register */
    volatile uint32_t M0AR;        /* 0x0C: Memory 0 address register */
    volatile uint32_t M1AR;        /* 0x10: Memory 1 address register */
    volatile uint32_t FCR;         /* 0x14: FIFO control register */
} DMA_Stream_TypeDef;

/* ---- DMA Controller ---- */
typedef struct {
    volatile uint32_t LISR;        /* 0x00: Low interrupt status register */
    volatile uint32_t HISR;        /* 0x04: High interrupt status register */
    volatile uint32_t LIFCR;       /* 0x08: Low interrupt flag clear register */
    volatile uint32_t HIFCR;       /* 0x0C: High interrupt flag clear register */
} DMA_TypeDef;

/* ---- ADC ---- */
typedef struct {
    volatile uint32_t SR;          /* 0x00: Status register */
    volatile uint32_t CR1;         /* 0x04: Control register 1 */
    volatile uint32_t CR2;         /* 0x08: Control register 2 */
    volatile uint32_t SMPR1;       /* 0x0C: Sample time register 1 */
    volatile uint32_t SMPR2;       /* 0x10: Sample time register 2 */
    volatile uint32_t JOFR1;       /* 0x14 */
    volatile uint32_t JOFR2;       /* 0x18 */
    volatile uint32_t JOFR3;       /* 0x1C */
    volatile uint32_t JOFR4;       /* 0x20 */
    volatile uint32_t HTR;         /* 0x24: Watchdog higher threshold register */
    volatile uint32_t LTR;         /* 0x28: Watchdog lower threshold register */
    volatile uint32_t SQR1;        /* 0x2C: Regular sequence register 1 */
    volatile uint32_t SQR2;        /* 0x30: Regular sequence register 2 */
    volatile uint32_t SQR3;        /* 0x34: Regular sequence register 3 */
    volatile uint32_t JSQR;        /* 0x38: Injected sequence register */
    volatile uint32_t JDR1;        /* 0x3C */
    volatile uint32_t JDR2;        /* 0x40 */
    volatile uint32_t JDR3;        /* 0x44 */
    volatile uint32_t JDR4;        /* 0x48 */
    volatile uint32_t DR;          /* 0x4C: Regular data register */
} ADC_TypeDef;

/* ---- ADC Common ---- */
typedef struct {
    volatile uint32_t CSR;         /* 0x00: Common status register */
    volatile uint32_t CCR;         /* 0x04: Common control register */
    volatile uint32_t CDR;         /* 0x08: Common regular data register */
} ADC_Common_TypeDef;

/* ---- EXTI ---- */
typedef struct {
    volatile uint32_t IMR;         /* 0x00: Interrupt mask register */
    volatile uint32_t EMR;         /* 0x04: Event mask register */
    volatile uint32_t RTSR;        /* 0x08: Rising trigger selection register */
    volatile uint32_t FTSR;        /* 0x0C: Falling trigger selection register */
    volatile uint32_t SWIER;       /* 0x10: Software interrupt event register */
    volatile uint32_t PR;          /* 0x14: Pending register */
} EXTI_TypeDef;

/* ---- SYSCFG ---- */
typedef struct {
    volatile uint32_t MEMRMP;      /* 0x00: Memory remap register */
    volatile uint32_t PMC;         /* 0x04 */
    volatile uint32_t EXTICR[4];   /* 0x08-0x14: External interrupt config registers */
    uint32_t RESERVED[2];
    volatile uint32_t CMPCR;       /* 0x20: Compensation cell control register */
} SYSCFG_TypeDef;

/* ---- FLASH Interface ---- */
typedef struct {
    volatile uint32_t ACR;         /* 0x00: Access control register */
    volatile uint32_t KEYR;        /* 0x04: Key register */
    volatile uint32_t OPTKEYR;     /* 0x08 */
    volatile uint32_t SR;          /* 0x0C: Status register */
    volatile uint32_t CR;          /* 0x10: Control register */
    volatile uint32_t OPTCR;       /* 0x14 */
    volatile uint32_t OPTCR1;      /* 0x18 */
} FLASH_TypeDef;

/* ---- PWR ---- */
typedef struct {
    volatile uint32_t CR;          /* 0x00: Power control register */
    volatile uint32_t CSR;         /* 0x04: Power control/status register */
} PWR_TypeDef;

/* ---- IWDG ---- */
typedef struct {
    volatile uint32_t KR;          /* 0x00: Key register */
    volatile uint32_t PR;          /* 0x04: Prescaler register */
    volatile uint32_t RLR;         /* 0x08: Reload register */
    volatile uint32_t SR;          /* 0x0C: Status register */
} IWDG_TypeDef;

/* ---- WWDG ---- */
typedef struct {
    volatile uint32_t CR;          /* 0x00: Control register */
    volatile uint32_t CFR;         /* 0x04: Configuration register */
    volatile uint32_t SR;          /* 0x08: Status register */
} WWDG_TypeDef;

/* ---- SysTick (ARM Core) ---- */
typedef struct {
    volatile uint32_t CTRL;        /* 0x00: Control and status register */
    volatile uint32_t LOAD;        /* 0x04: Reload value register */
    volatile uint32_t VAL;         /* 0x08: Current value register */
    volatile uint32_t CALIB;       /* 0x0C: Calibration register */
} SysTick_TypeDef;

/* ---- NVIC (ARM Core) ---- */
typedef struct {
    volatile uint32_t ISER[8];     /* 0x000: Interrupt Set Enable Registers */
    uint32_t RESERVED0[24];
    volatile uint32_t ICER[8];     /* 0x080: Interrupt Clear Enable Registers */
    uint32_t RESERVED1[24];
    volatile uint32_t ISPR[8];     /* 0x100: Interrupt Set Pending Registers */
    uint32_t RESERVED2[24];
    volatile uint32_t ICPR[8];     /* 0x180: Interrupt Clear Pending Registers */
    uint32_t RESERVED3[24];
    volatile uint32_t IABR[8];     /* 0x200: Interrupt Active Bit Registers */
    uint32_t RESERVED4[56];
    volatile uint8_t  IPR[240];    /* 0x300: Interrupt Priority Registers */
    uint32_t RESERVED5[644];
    volatile uint32_t STIR;        /* 0xE00: Software Trigger Interrupt Register */
} NVIC_TypeDef;

/* ---- SCB (System Control Block) ---- */
typedef struct {
    volatile uint32_t CPUID;       /* 0x00 */
    volatile uint32_t ICSR;        /* 0x04: Interrupt control and state register */
    volatile uint32_t VTOR;        /* 0x08: Vector table offset register */
    volatile uint32_t AIRCR;       /* 0x0C: Application interrupt/reset control */
    volatile uint32_t SCR;         /* 0x10: System control register */
    volatile uint32_t CCR;         /* 0x14: Configuration control register */
    volatile uint8_t  SHPR[12];    /* 0x18: System handler priority registers */
    volatile uint32_t SHCSR;       /* 0x24: System handler control and state */
    volatile uint32_t CFSR;        /* 0x28: Configurable fault status register */
    volatile uint32_t HFSR;        /* 0x2C: Hard fault status register */
    volatile uint32_t DFSR;        /* 0x30: Debug fault status register */
    volatile uint32_t MMFAR;       /* 0x34: MemManage fault address register */
    volatile uint32_t BFAR;        /* 0x38: BusFault address register */
    volatile uint32_t AFSR;        /* 0x3C: Auxiliary fault status register */
} SCB_TypeDef;

/* ========================================================================= */
/*                     Peripheral Instance Definitions                       */
/* ========================================================================= */

/* GPIO */
#define GPIOA               ((GPIO_TypeDef *) (AHB1_BASE + 0x0000UL))
#define GPIOB               ((GPIO_TypeDef *) (AHB1_BASE + 0x0400UL))
#define GPIOC               ((GPIO_TypeDef *) (AHB1_BASE + 0x0800UL))
#define GPIOD               ((GPIO_TypeDef *) (AHB1_BASE + 0x0C00UL))
#define GPIOE               ((GPIO_TypeDef *) (AHB1_BASE + 0x1000UL))
#define GPIOF               ((GPIO_TypeDef *) (AHB1_BASE + 0x1400UL))
#define GPIOG               ((GPIO_TypeDef *) (AHB1_BASE + 0x1800UL))
#define GPIOH               ((GPIO_TypeDef *) (AHB1_BASE + 0x1C00UL))

/* RCC */
#define RCC                 ((RCC_TypeDef *) (AHB1_BASE + 0x3800UL))

/* Flash */
#define FLASH_IF            ((FLASH_TypeDef *) (AHB1_BASE + 0x3C00UL))

/* DMA */
#define DMA1                ((DMA_TypeDef *) (AHB1_BASE + 0x6000UL))
#define DMA2                ((DMA_TypeDef *) (AHB1_BASE + 0x6400UL))

#define DMA1_Stream0        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6010UL))
#define DMA1_Stream1        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6028UL))
#define DMA1_Stream2        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6040UL))
#define DMA1_Stream3        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6058UL))
#define DMA1_Stream4        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6070UL))
#define DMA1_Stream5        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6088UL))
#define DMA1_Stream6        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x60A0UL))
#define DMA1_Stream7        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x60B8UL))

#define DMA2_Stream0        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6410UL))
#define DMA2_Stream1        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6428UL))
#define DMA2_Stream2        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6440UL))
#define DMA2_Stream3        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6458UL))
#define DMA2_Stream4        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6470UL))
#define DMA2_Stream5        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x6488UL))
#define DMA2_Stream6        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x64A0UL))
#define DMA2_Stream7        ((DMA_Stream_TypeDef *) (AHB1_BASE + 0x64B8UL))

/* Timers */
#define TIM2                ((TIM_TypeDef *) (APB1_BASE + 0x0000UL))
#define TIM3                ((TIM_TypeDef *) (APB1_BASE + 0x0400UL))
#define TIM4                ((TIM_TypeDef *) (APB1_BASE + 0x0800UL))
#define TIM5                ((TIM_TypeDef *) (APB1_BASE + 0x0C00UL))
#define TIM1                ((TIM_TypeDef *) (APB2_BASE + 0x0000UL))

/* USART */
#define USART1              ((USART_TypeDef *) (APB2_BASE + 0x1000UL))
#define USART2              ((USART_TypeDef *) (APB1_BASE + 0x4400UL))
#define USART3              ((USART_TypeDef *) (APB1_BASE + 0x4800UL))
#define USART6              ((USART_TypeDef *) (APB2_BASE + 0x1400UL))

/* SPI */
#define SPI1                ((SPI_TypeDef *) (APB2_BASE + 0x3000UL))
#define SPI2                ((SPI_TypeDef *) (APB1_BASE + 0x3800UL))
#define SPI3                ((SPI_TypeDef *) (APB1_BASE + 0x3C00UL))
#define SPI4                ((SPI_TypeDef *) (APB2_BASE + 0x3400UL))

/* I2C */
#define I2C1                ((I2C_TypeDef *) (APB1_BASE + 0x5400UL))
#define I2C2                ((I2C_TypeDef *) (APB1_BASE + 0x5800UL))
#define I2C3                ((I2C_TypeDef *) (APB1_BASE + 0x5C00UL))

/* ADC */
#define ADC1                ((ADC_TypeDef *) (APB2_BASE + 0x2000UL))
#define ADC_COMMON          ((ADC_Common_TypeDef *) (APB2_BASE + 0x2300UL))

/* EXTI */
#define EXTI                ((EXTI_TypeDef *) (APB2_BASE + 0x3C00UL))

/* SYSCFG */
#define SYSCFG              ((SYSCFG_TypeDef *) (APB2_BASE + 0x3800UL))

/* PWR */
#define PWR                 ((PWR_TypeDef *) (APB1_BASE + 0x7000UL))

/* IWDG */
#define IWDG                ((IWDG_TypeDef *) (APB1_BASE + 0x3000UL))

/* WWDG */
#define WWDG                ((WWDG_TypeDef *) (APB1_BASE + 0x2C00UL))

/* ARM Core */
#define SysTick             ((SysTick_TypeDef *) SYSTICK_BASE)
#define NVIC                ((NVIC_TypeDef *) NVIC_BASE)
#define SCB                 ((SCB_TypeDef *) SCB_BASE)

/* ========================================================================= */
/*                        IRQ Number Definitions                             */
/* ========================================================================= */

typedef enum {
    NonMaskableInt_IRQn     = -14,
    MemoryManagement_IRQn   = -12,
    BusFault_IRQn           = -11,
    UsageFault_IRQn         = -10,
    SVCall_IRQn             = -5,
    DebugMonitor_IRQn       = -4,
    PendSV_IRQn             = -2,
    SysTick_IRQn            = -1,

    WWDG_IRQn               = 0,
    PVD_IRQn                = 1,
    TAMP_STAMP_IRQn         = 2,
    RTC_WKUP_IRQn           = 3,
    FLASH_IRQn              = 4,
    RCC_IRQn                = 5,
    EXTI0_IRQn              = 6,
    EXTI1_IRQn              = 7,
    EXTI2_IRQn              = 8,
    EXTI3_IRQn              = 9,
    EXTI4_IRQn              = 10,
    DMA1_Stream0_IRQn       = 11,
    DMA1_Stream1_IRQn       = 12,
    DMA1_Stream2_IRQn       = 13,
    DMA1_Stream3_IRQn       = 14,
    DMA1_Stream4_IRQn       = 15,
    DMA1_Stream5_IRQn       = 16,
    DMA1_Stream6_IRQn       = 17,
    ADC_IRQn                = 18,
    CAN1_TX_IRQn            = 19,
    CAN1_RX0_IRQn           = 20,
    CAN1_RX1_IRQn           = 21,
    CAN1_SCE_IRQn           = 22,
    EXTI9_5_IRQn            = 23,
    TIM1_BRK_TIM9_IRQn      = 24,
    TIM1_UP_TIM10_IRQn      = 25,
    TIM1_TRG_COM_TIM11_IRQn = 26,
    TIM1_CC_IRQn            = 27,
    TIM2_IRQn               = 28,
    TIM3_IRQn               = 29,
    TIM4_IRQn               = 30,
    I2C1_EV_IRQn            = 31,
    I2C1_ER_IRQn            = 32,
    I2C2_EV_IRQn            = 33,
    I2C2_ER_IRQn            = 34,
    SPI1_IRQn               = 35,
    SPI2_IRQn               = 36,
    USART1_IRQn             = 37,
    USART2_IRQn             = 38,
    USART3_IRQn             = 39,
    EXTI15_10_IRQn          = 40,
    RTC_Alarm_IRQn          = 41,
    OTG_FS_WKUP_IRQn        = 42,
    TIM8_BRK_TIM12_IRQn     = 43,
    TIM8_UP_TIM13_IRQn      = 44,
    TIM8_TRG_COM_TIM14_IRQn = 45,
    TIM8_CC_IRQn            = 46,
    DMA1_Stream7_IRQn       = 47,
    FMC_IRQn                = 48,
    SDIO_IRQn               = 49,
    TIM5_IRQn               = 50,
    SPI3_IRQn               = 51,
    UART4_IRQn              = 52,
    UART5_IRQn              = 53,
    TIM6_DAC_IRQn           = 54,
    TIM7_IRQn               = 55,
    DMA2_Stream0_IRQn       = 56,
    DMA2_Stream1_IRQn       = 57,
    DMA2_Stream2_IRQn       = 58,
    DMA2_Stream3_IRQn       = 59,
    DMA2_Stream4_IRQn       = 60,
    OTG_FS_IRQn             = 67,
    DMA2_Stream5_IRQn       = 68,
    DMA2_Stream6_IRQn       = 69,
    DMA2_Stream7_IRQn       = 70,
    USART6_IRQn             = 71,
    I2C3_EV_IRQn            = 72,
    I2C3_ER_IRQn            = 73,
    OTG_HS_EP1_OUT_IRQn     = 74,
    OTG_HS_EP1_IN_IRQn      = 75,
    OTG_HS_WKUP_IRQn        = 76,
    OTG_HS_IRQn             = 77,
    DCMI_IRQn               = 78,
    FPU_IRQn                = 81,
    SPI4_IRQn               = 84,
    SAI1_IRQn               = 87,
    SAI2_IRQn               = 91,
    QUADSPI_IRQn            = 92,
    HDMI_CEC_IRQn           = 93,
    SPDIF_RX_IRQn           = 94,
    FMPI2C1_EV_IRQn         = 95,
    FMPI2C1_ER_IRQn         = 96,
} IRQn_Type;

/* ========================================================================= */
/*                        RCC Bit Definitions                                */
/* ========================================================================= */

/* RCC_CR */
#define RCC_CR_HSION        (1U << 0)
#define RCC_CR_HSIRDY       (1U << 1)
#define RCC_CR_HSEON        (1U << 16)
#define RCC_CR_HSERDY       (1U << 17)
#define RCC_CR_HSEBYP       (1U << 18)
#define RCC_CR_CSSON        (1U << 19)
#define RCC_CR_PLLON        (1U << 24)
#define RCC_CR_PLLRDY       (1U << 25)
#define RCC_CR_PLLI2SON     (1U << 26)
#define RCC_CR_PLLI2SRDY    (1U << 27)
#define RCC_CR_PLLSAION     (1U << 28)
#define RCC_CR_PLLSAIRDY    (1U << 29)

/* RCC_PLLCFGR */
#define RCC_PLLCFGR_PLLM_Pos   0
#define RCC_PLLCFGR_PLLM_Msk   (0x3FUL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLN_Pos   6
#define RCC_PLLCFGR_PLLN_Msk   (0x1FFUL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLP_Pos   16
#define RCC_PLLCFGR_PLLP_Msk   (0x3UL << RCC_PLLCFGR_PLLP_Pos)
#define RCC_PLLCFGR_PLLSRC     (1U << 22)
#define RCC_PLLCFGR_PLLSRC_HSE (1U << 22)
#define RCC_PLLCFGR_PLLSRC_HSI 0U
#define RCC_PLLCFGR_PLLQ_Pos   24
#define RCC_PLLCFGR_PLLQ_Msk   (0xFUL << RCC_PLLCFGR_PLLQ_Pos)

/* RCC_CFGR */
#define RCC_CFGR_SW_Pos     0
#define RCC_CFGR_SW_Msk     (0x3UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_HSI     (0x0UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_HSE     (0x1UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_PLL     (0x2UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SWS_Pos    2
#define RCC_CFGR_SWS_Msk    (0x3UL << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS_HSI    (0x0UL << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS_HSE    (0x1UL << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS_PLL    (0x2UL << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_HPRE_Pos   4
#define RCC_CFGR_HPRE_Msk   (0xFUL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_PPRE1_Pos  10
#define RCC_CFGR_PPRE1_Msk  (0x7UL << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE2_Pos  13
#define RCC_CFGR_PPRE2_Msk  (0x7UL << RCC_CFGR_PPRE2_Pos)

/* RCC_AHB1ENR */
#define RCC_AHB1ENR_GPIOAEN (1U << 0)
#define RCC_AHB1ENR_GPIOBEN (1U << 1)
#define RCC_AHB1ENR_GPIOCEN (1U << 2)
#define RCC_AHB1ENR_GPIODEN (1U << 3)
#define RCC_AHB1ENR_GPIOEEN (1U << 4)
#define RCC_AHB1ENR_GPIOFEN (1U << 5)
#define RCC_AHB1ENR_GPIOGEN (1U << 6)
#define RCC_AHB1ENR_GPIOHEN (1U << 7)
#define RCC_AHB1ENR_DMA1EN  (1U << 21)
#define RCC_AHB1ENR_DMA2EN  (1U << 22)

/* RCC_APB1ENR */
#define RCC_APB1ENR_TIM2EN   (1U << 0)
#define RCC_APB1ENR_TIM3EN   (1U << 1)
#define RCC_APB1ENR_TIM4EN   (1U << 2)
#define RCC_APB1ENR_TIM5EN   (1U << 3)
#define RCC_APB1ENR_TIM6EN   (1U << 4)
#define RCC_APB1ENR_TIM7EN   (1U << 5)
#define RCC_APB1ENR_WWDGEN   (1U << 11)
#define RCC_APB1ENR_SPI2EN   (1U << 14)
#define RCC_APB1ENR_SPI3EN   (1U << 15)
#define RCC_APB1ENR_USART2EN (1U << 17)
#define RCC_APB1ENR_USART3EN (1U << 18)
#define RCC_APB1ENR_I2C1EN   (1U << 21)
#define RCC_APB1ENR_I2C2EN   (1U << 22)
#define RCC_APB1ENR_I2C3EN   (1U << 23)
#define RCC_APB1ENR_PWREN    (1U << 28)

/* RCC_APB2ENR */
#define RCC_APB2ENR_TIM1EN   (1U << 0)
#define RCC_APB2ENR_USART1EN (1U << 4)
#define RCC_APB2ENR_USART6EN (1U << 5)
#define RCC_APB2ENR_ADC1EN   (1U << 8)
#define RCC_APB2ENR_SPI1EN   (1U << 12)
#define RCC_APB2ENR_SYSCFGEN (1U << 14)
#define RCC_APB2ENR_TIM9EN   (1U << 16)
#define RCC_APB2ENR_TIM10EN  (1U << 17)
#define RCC_APB2ENR_TIM11EN  (1U << 18)

/* ========================================================================= */
/*                        GPIO Bit Definitions                               */
/* ========================================================================= */

/* MODER: 2 bits per pin */
#define GPIO_MODER_INPUT     0x0U
#define GPIO_MODER_OUTPUT    0x1U
#define GPIO_MODER_AF        0x2U
#define GPIO_MODER_ANALOG    0x3U

/* OTYPER: 1 bit per pin */
#define GPIO_OTYPER_PP       0x0U    /* Push-pull */
#define GPIO_OTYPER_OD       0x1U    /* Open-drain */

/* OSPEEDR: 2 bits per pin */
#define GPIO_OSPEEDR_LOW     0x0U
#define GPIO_OSPEEDR_MED     0x1U
#define GPIO_OSPEEDR_FAST    0x2U
#define GPIO_OSPEEDR_HIGH    0x3U

/* PUPDR: 2 bits per pin */
#define GPIO_PUPDR_NONE      0x0U
#define GPIO_PUPDR_PU        0x1U    /* Pull-up */
#define GPIO_PUPDR_PD        0x2U    /* Pull-down */

/* Alternate Function numbers */
#define GPIO_AF0_SYSTEM      0x0U
#define GPIO_AF1_TIM1_2      0x1U
#define GPIO_AF2_TIM3_5      0x2U
#define GPIO_AF3_TIM9_11     0x3U
#define GPIO_AF4_I2C         0x4U
#define GPIO_AF5_SPI         0x5U
#define GPIO_AF6_SPI3        0x6U
#define GPIO_AF7_USART       0x7U
#define GPIO_AF8_UART        0x8U
#define GPIO_AF9_CAN_TIM     0x9U
#define GPIO_AF10_OTG        0xAU
#define GPIO_AF12_FMC_SDIO   0xCU
#define GPIO_AF15_EVENTOUT   0xFU

/* Nucleo-F446RE on-board LED and button */
#define LED_PIN              5       /* PA5 = LD2 */
#define LED_PORT             GPIOA
#define BTN_PIN              13      /* PC13 = B1 (active low) */
#define BTN_PORT             GPIOC

/* ========================================================================= */
/*                       USART Bit Definitions                               */
/* ========================================================================= */

/* USART_SR */
#define USART_SR_PE          (1U << 0)
#define USART_SR_FE          (1U << 1)
#define USART_SR_NF          (1U << 2)
#define USART_SR_ORE         (1U << 3)
#define USART_SR_IDLE        (1U << 4)
#define USART_SR_RXNE        (1U << 5)
#define USART_SR_TC          (1U << 6)
#define USART_SR_TXE         (1U << 7)
#define USART_SR_LBD         (1U << 8)
#define USART_SR_CTS         (1U << 9)

/* USART_CR1 */
#define USART_CR1_SBK        (1U << 0)
#define USART_CR1_RWU        (1U << 1)
#define USART_CR1_RE         (1U << 2)
#define USART_CR1_TE         (1U << 3)
#define USART_CR1_IDLEIE     (1U << 4)
#define USART_CR1_RXNEIE     (1U << 5)
#define USART_CR1_TCIE       (1U << 6)
#define USART_CR1_TXEIE      (1U << 7)
#define USART_CR1_PEIE       (1U << 8)
#define USART_CR1_PS         (1U << 9)
#define USART_CR1_PCE        (1U << 10)
#define USART_CR1_WAKE       (1U << 11)
#define USART_CR1_M          (1U << 12)
#define USART_CR1_UE         (1U << 13)
#define USART_CR1_OVER8      (1U << 15)

/* USART_CR3 */
#define USART_CR3_DMAT       (1U << 7)
#define USART_CR3_DMAR       (1U << 6)

/* ========================================================================= */
/*                        SPI Bit Definitions                                */
/* ========================================================================= */

/* SPI_CR1 */
#define SPI_CR1_CPHA         (1U << 0)
#define SPI_CR1_CPOL         (1U << 1)
#define SPI_CR1_MSTR         (1U << 2)
#define SPI_CR1_BR_Pos       3
#define SPI_CR1_BR_Msk       (0x7UL << SPI_CR1_BR_Pos)
#define SPI_CR1_SPE          (1U << 6)
#define SPI_CR1_LSBFIRST     (1U << 7)
#define SPI_CR1_SSI          (1U << 8)
#define SPI_CR1_SSM          (1U << 9)
#define SPI_CR1_RXONLY       (1U << 10)
#define SPI_CR1_DFF          (1U << 11)
#define SPI_CR1_BIDIOE       (1U << 14)
#define SPI_CR1_BIDIMODE     (1U << 15)

/* SPI_CR2 */
#define SPI_CR2_RXDMAEN      (1U << 0)
#define SPI_CR2_TXDMAEN      (1U << 1)
#define SPI_CR2_SSOE         (1U << 2)
#define SPI_CR2_ERRIE        (1U << 5)
#define SPI_CR2_RXNEIE       (1U << 6)
#define SPI_CR2_TXEIE        (1U << 7)

/* SPI_SR */
#define SPI_SR_RXNE          (1U << 0)
#define SPI_SR_TXE           (1U << 1)
#define SPI_SR_MODF          (1U << 5)
#define SPI_SR_OVR           (1U << 6)
#define SPI_SR_BSY           (1U << 7)

/* ========================================================================= */
/*                        I2C Bit Definitions                                */
/* ========================================================================= */

/* I2C_CR1 */
#define I2C_CR1_PE           (1U << 0)
#define I2C_CR1_SMBUS        (1U << 1)
#define I2C_CR1_NOSTRETCH    (1U << 7)
#define I2C_CR1_START        (1U << 8)
#define I2C_CR1_STOP         (1U << 9)
#define I2C_CR1_ACK          (1U << 10)
#define I2C_CR1_POS          (1U << 11)
#define I2C_CR1_SWRST        (1U << 15)

/* I2C_CR2 */
#define I2C_CR2_FREQ_Pos     0
#define I2C_CR2_FREQ_Msk     (0x3FUL << I2C_CR2_FREQ_Pos)
#define I2C_CR2_ITERREN      (1U << 8)
#define I2C_CR2_ITEVTEN      (1U << 9)
#define I2C_CR2_ITBUFEN      (1U << 10)
#define I2C_CR2_DMAEN        (1U << 11)
#define I2C_CR2_LAST         (1U << 12)

/* I2C_SR1 */
#define I2C_SR1_SB           (1U << 0)
#define I2C_SR1_ADDR         (1U << 1)
#define I2C_SR1_BTF          (1U << 2)
#define I2C_SR1_STOPF        (1U << 4)
#define I2C_SR1_RXNE         (1U << 6)
#define I2C_SR1_TXE          (1U << 7)
#define I2C_SR1_BERR         (1U << 8)
#define I2C_SR1_ARLO         (1U << 9)
#define I2C_SR1_AF           (1U << 10)
#define I2C_SR1_OVR          (1U << 11)

/* I2C_SR2 */
#define I2C_SR2_MSL          (1U << 0)
#define I2C_SR2_BUSY         (1U << 1)
#define I2C_SR2_TRA          (1U << 2)

/* I2C_CCR */
#define I2C_CCR_CCR_Pos      0
#define I2C_CCR_CCR_Msk      (0xFFFUL << I2C_CCR_CCR_Pos)
#define I2C_CCR_DUTY         (1U << 14)
#define I2C_CCR_FS           (1U << 15)

/* ========================================================================= */
/*                        TIM Bit Definitions                                */
/* ========================================================================= */

/* TIM_CR1 */
#define TIM_CR1_CEN          (1U << 0)
#define TIM_CR1_UDIS         (1U << 1)
#define TIM_CR1_URS          (1U << 2)
#define TIM_CR1_OPM          (1U << 3)
#define TIM_CR1_DIR          (1U << 4)
#define TIM_CR1_ARPE         (1U << 7)

/* TIM_DIER */
#define TIM_DIER_UIE         (1U << 0)
#define TIM_DIER_CC1IE       (1U << 1)
#define TIM_DIER_CC2IE       (1U << 2)
#define TIM_DIER_CC3IE       (1U << 3)
#define TIM_DIER_CC4IE       (1U << 4)
#define TIM_DIER_TIE         (1U << 6)
#define TIM_DIER_UDE         (1U << 8)
#define TIM_DIER_CC1DE       (1U << 9)

/* TIM_SR */
#define TIM_SR_UIF           (1U << 0)
#define TIM_SR_CC1IF         (1U << 1)
#define TIM_SR_CC2IF         (1U << 2)
#define TIM_SR_CC3IF         (1U << 3)
#define TIM_SR_CC4IF         (1U << 4)

/* TIM_EGR */
#define TIM_EGR_UG           (1U << 0)

/* TIM_CCMR1 (Output Compare) */
#define TIM_CCMR1_OC1M_Pos   4
#define TIM_CCMR1_OC1M_Msk   (0x7UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M_PWM1  (0x6UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M_PWM2  (0x7UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1PE      (1U << 3)
#define TIM_CCMR1_CC1S_Pos   0
#define TIM_CCMR1_CC1S_Msk   (0x3UL << TIM_CCMR1_CC1S_Pos)

/* TIM_CCMR1 (Input Capture) */
#define TIM_CCMR1_IC1F_Pos   4
#define TIM_CCMR1_IC1PSC_Pos 2

/* TIM_CCER */
#define TIM_CCER_CC1E        (1U << 0)
#define TIM_CCER_CC1P        (1U << 1)
#define TIM_CCER_CC2E        (1U << 4)
#define TIM_CCER_CC2P        (1U << 5)
#define TIM_CCER_CC3E        (1U << 8)
#define TIM_CCER_CC4E        (1U << 12)

/* ========================================================================= */
/*                        DMA Bit Definitions                                */
/* ========================================================================= */

/* DMA_SxCR */
#define DMA_SxCR_EN          (1U << 0)
#define DMA_SxCR_DMEIE       (1U << 1)
#define DMA_SxCR_TEIE        (1U << 2)
#define DMA_SxCR_HTIE        (1U << 3)
#define DMA_SxCR_TCIE        (1U << 4)
#define DMA_SxCR_PFCTRL      (1U << 5)
#define DMA_SxCR_DIR_Pos     6
#define DMA_SxCR_DIR_Msk     (0x3UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_DIR_P2M     (0x0UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_DIR_M2P     (0x1UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_DIR_M2M     (0x2UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_CIRC        (1U << 8)
#define DMA_SxCR_PINC        (1U << 9)
#define DMA_SxCR_MINC        (1U << 10)
#define DMA_SxCR_PSIZE_Pos   11
#define DMA_SxCR_PSIZE_Msk   (0x3UL << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_MSIZE_Pos   13
#define DMA_SxCR_MSIZE_Msk   (0x3UL << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_PL_Pos      16
#define DMA_SxCR_PL_Msk      (0x3UL << DMA_SxCR_PL_Pos)
#define DMA_SxCR_DBM         (1U << 18)
#define DMA_SxCR_CHSEL_Pos   25
#define DMA_SxCR_CHSEL_Msk   (0x7UL << DMA_SxCR_CHSEL_Pos)

/* DMA_LISR / HISR flag positions for stream 0 (shift by 6/16/22 for streams 1-3) */
#define DMA_LISR_TCIF0       (1U << 5)
#define DMA_LISR_HTIF0       (1U << 4)
#define DMA_LISR_TEIF0       (1U << 3)
#define DMA_LISR_DMEIF0      (1U << 2)
#define DMA_LISR_FEIF0       (1U << 0)

/* Stream 1 */
#define DMA_LISR_TCIF1       (1U << 11)
#define DMA_LISR_HTIF1       (1U << 10)
#define DMA_LISR_TEIF1       (1U << 9)

/* Stream 2 */
#define DMA_LISR_TCIF2       (1U << 21)
#define DMA_LISR_HTIF2       (1U << 20)
#define DMA_LISR_TEIF2       (1U << 19)

/* Stream 3 */
#define DMA_LISR_TCIF3       (1U << 27)
#define DMA_LISR_HTIF3       (1U << 26)
#define DMA_LISR_TEIF3       (1U << 25)

/* Streams 4-7 use HISR (same offsets as 0-3) */
#define DMA_HISR_TCIF4       (1U << 5)
#define DMA_HISR_TCIF5       (1U << 11)
#define DMA_HISR_TCIF6       (1U << 21)
#define DMA_HISR_TCIF7       (1U << 27)

/* LIFCR / HIFCR (same bit positions as LISR/HISR) */
#define DMA_LIFCR_CTCIF0     (1U << 5)
#define DMA_LIFCR_CTCIF1     (1U << 11)
#define DMA_LIFCR_CTCIF2     (1U << 21)
#define DMA_LIFCR_CTCIF3     (1U << 27)
#define DMA_HIFCR_CTCIF4     (1U << 5)
#define DMA_HIFCR_CTCIF5     (1U << 11)
#define DMA_HIFCR_CTCIF6     (1U << 21)
#define DMA_HIFCR_CTCIF7     (1U << 27)

/* ========================================================================= */
/*                        ADC Bit Definitions                                */
/* ========================================================================= */

/* ADC_SR */
#define ADC_SR_AWD           (1U << 0)
#define ADC_SR_EOC           (1U << 1)
#define ADC_SR_JEOC          (1U << 2)
#define ADC_SR_JSTRT         (1U << 3)
#define ADC_SR_STRT          (1U << 4)
#define ADC_SR_OVR           (1U << 5)

/* ADC_CR1 */
#define ADC_CR1_EOCIE        (1U << 5)
#define ADC_CR1_SCAN         (1U << 8)
#define ADC_CR1_RES_Pos      24
#define ADC_CR1_RES_Msk      (0x3UL << ADC_CR1_RES_Pos)
#define ADC_CR1_RES_12BIT    (0x0UL << ADC_CR1_RES_Pos)
#define ADC_CR1_RES_10BIT    (0x1UL << ADC_CR1_RES_Pos)
#define ADC_CR1_RES_8BIT     (0x2UL << ADC_CR1_RES_Pos)
#define ADC_CR1_RES_6BIT     (0x3UL << ADC_CR1_RES_Pos)
#define ADC_CR1_OVRIE        (1U << 26)

/* ADC_CR2 */
#define ADC_CR2_ADON         (1U << 0)
#define ADC_CR2_CONT         (1U << 1)
#define ADC_CR2_DMA          (1U << 8)
#define ADC_CR2_DDS          (1U << 9)
#define ADC_CR2_EOCS         (1U << 10)
#define ADC_CR2_ALIGN        (1U << 11)
#define ADC_CR2_SWSTART      (1U << 30)

/* ADC_SQR1 */
#define ADC_SQR1_L_Pos       20
#define ADC_SQR1_L_Msk       (0xFUL << ADC_SQR1_L_Pos)

/* ADC_SQR3 */
#define ADC_SQR3_SQ1_Pos     0
#define ADC_SQR3_SQ1_Msk     (0x1FUL << ADC_SQR3_SQ1_Pos)

/* ADC_SMPR2 */
#define ADC_SMPR2_SMP0_Pos   0
#define ADC_SMPR2_SMP_3CYC   0x0U
#define ADC_SMPR2_SMP_15CYC  0x1U
#define ADC_SMPR2_SMP_28CYC  0x2U
#define ADC_SMPR2_SMP_56CYC  0x3U
#define ADC_SMPR2_SMP_84CYC  0x4U
#define ADC_SMPR2_SMP_112CYC 0x5U
#define ADC_SMPR2_SMP_144CYC 0x6U
#define ADC_SMPR2_SMP_480CYC 0x7U

/* ADC_CCR (Common) */
#define ADC_CCR_ADCPRE_Pos   16
#define ADC_CCR_ADCPRE_DIV2  (0x0UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CCR_ADCPRE_DIV4  (0x1UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CCR_ADCPRE_DIV6  (0x2UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CCR_ADCPRE_DIV8  (0x3UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CCR_TSVREFE      (1U << 23)

/* ========================================================================= */
/*                        EXTI Bit Definitions                               */
/* ========================================================================= */

#define EXTI_IMR_LINE(n)     (1U << (n))
#define EXTI_RTSR_LINE(n)    (1U << (n))
#define EXTI_FTSR_LINE(n)    (1U << (n))
#define EXTI_PR_LINE(n)      (1U << (n))

/* ========================================================================= */
/*                      SYSCFG Bit Definitions                               */
/* ========================================================================= */

/* SYSCFG_EXTICR: 4 bits per EXTI line, port selection */
#define SYSCFG_EXTICR_PA     0x0U
#define SYSCFG_EXTICR_PB     0x1U
#define SYSCFG_EXTICR_PC     0x2U
#define SYSCFG_EXTICR_PD     0x3U
#define SYSCFG_EXTICR_PE     0x4U
#define SYSCFG_EXTICR_PH     0x7U

/* ========================================================================= */
/*                       FLASH Bit Definitions                               */
/* ========================================================================= */

/* FLASH_ACR */
#define FLASH_ACR_LATENCY_Pos 0
#define FLASH_ACR_LATENCY_Msk (0xFUL << FLASH_ACR_LATENCY_Pos)
#define FLASH_ACR_PRFTEN      (1U << 8)
#define FLASH_ACR_ICEN        (1U << 9)
#define FLASH_ACR_DCEN        (1U << 10)

/* ========================================================================= */
/*                        PWR Bit Definitions                                */
/* ========================================================================= */

/* PWR_CR */
#define PWR_CR_LPDS          (1U << 0)
#define PWR_CR_PDDS          (1U << 1)
#define PWR_CR_CWUF          (1U << 2)
#define PWR_CR_VOS_Pos       14
#define PWR_CR_VOS_Msk       (0x3UL << PWR_CR_VOS_Pos)
#define PWR_CR_VOS_SCALE1    (0x3UL << PWR_CR_VOS_Pos)
#define PWR_CR_VOS_SCALE2    (0x2UL << PWR_CR_VOS_Pos)
#define PWR_CR_VOS_SCALE3    (0x1UL << PWR_CR_VOS_Pos)
#define PWR_CR_ODEN          (1U << 16)
#define PWR_CR_ODSWEN        (1U << 17)

/* PWR_CSR */
#define PWR_CSR_WUF          (1U << 0)
#define PWR_CSR_ODRDY        (1U << 16)
#define PWR_CSR_ODSWRDY      (1U << 17)

/* ========================================================================= */
/*                      IWDG Bit Definitions                                 */
/* ========================================================================= */

#define IWDG_KR_START        0xCCCCU
#define IWDG_KR_RELOAD       0xAAAAU
#define IWDG_KR_UNLOCK       0x5555U

#define IWDG_PR_DIV4         0x0U
#define IWDG_PR_DIV8         0x1U
#define IWDG_PR_DIV16        0x2U
#define IWDG_PR_DIV32        0x3U
#define IWDG_PR_DIV64        0x4U
#define IWDG_PR_DIV128       0x5U
#define IWDG_PR_DIV256       0x6U

/* ========================================================================= */
/*                      WWDG Bit Definitions                                 */
/* ========================================================================= */

#define WWDG_CR_WDGA         (1U << 7)
#define WWDG_CFR_EWI         (1U << 9)
#define WWDG_CFR_WDGTB_Pos   7

/* ========================================================================= */
/*                     SysTick Bit Definitions                               */
/* ========================================================================= */

#define SYSTICK_CTRL_ENABLE    (1U << 0)
#define SYSTICK_CTRL_TICKINT   (1U << 1)
#define SYSTICK_CTRL_CLKSOURCE (1U << 2)
#define SYSTICK_CTRL_COUNTFLAG (1U << 16)

/* ========================================================================= */
/*                     SCB Bit Definitions                                   */
/* ========================================================================= */

#define SCB_AIRCR_VECTKEY     (0x05FAUL << 16)
#define SCB_AIRCR_PRIGROUP_Pos 8
#define SCB_AIRCR_SYSRESETREQ (1U << 2)
#define SCB_SCR_SLEEPDEEP     (1U << 2)
#define SCB_SCR_SLEEPONEXIT   (1U << 1)

/* ========================================================================= */
/*                        Inline Helper Functions                            */
/* ========================================================================= */

static inline void NVIC_EnableIRQ(IRQn_Type irq) {
    NVIC->ISER[((uint32_t)irq) >> 5] = (1UL << (((uint32_t)irq) & 0x1FUL));
}

static inline void NVIC_DisableIRQ(IRQn_Type irq) {
    NVIC->ICER[((uint32_t)irq) >> 5] = (1UL << (((uint32_t)irq) & 0x1FUL));
}

static inline void NVIC_SetPriority(IRQn_Type irq, uint32_t priority) {
    if ((int32_t)irq >= 0) {
        NVIC->IPR[(uint32_t)irq] = (uint8_t)((priority << 4) & 0xFFUL);
    } else {
        SCB->SHPR[(((uint32_t)irq) & 0xFUL) - 4UL] =
            (uint8_t)((priority << 4) & 0xFFUL);
    }
}

static inline void NVIC_ClearPending(IRQn_Type irq) {
    NVIC->ICPR[((uint32_t)irq) >> 5] = (1UL << (((uint32_t)irq) & 0x1FUL));
}

static inline void __disable_irq(void) {
    __asm volatile ("cpsid i" ::: "memory");
}

static inline void __enable_irq(void) {
    __asm volatile ("cpsie i" ::: "memory");
}

static inline void __WFI(void) {
    __asm volatile ("wfi" ::: "memory");
}

static inline void __DSB(void) {
    __asm volatile ("dsb 0xF" ::: "memory");
}

static inline void __ISB(void) {
    __asm volatile ("isb 0xF" ::: "memory");
}

static inline void __NOP(void) {
    __asm volatile ("nop");
}

#endif /* STM32F446RE_H */
