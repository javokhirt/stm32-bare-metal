# STM32 Bare-Metal Firmware

a progressive series of bare-metal firmware projects on the STM32F411RE (ARM Cortex-M4), written without HAL, LL, or CubeMX; every peripheral is driven by reading the reference manual (RM0383) and writing registers directly.

**Toolchain:** `arm-none-eabi-gcc` · Make · OpenOCD · GDB over SWD — fully terminal-driven, no IDE.
**Board:** STM32F411RE Nucleo.

Each numbered folder is a self-contained lesson that builds on the previous one, going from blinking an LED with raw register writes up to timer output-compare and a modular interrupt-driven UART driver.

---

## Project progression

| # | Project | What it covers | Key peripheral / register |
|---|---------|----------------|---------------------------|
| 01 | led-toggle | First GPIO output — turning on an LED via direct register writes | `RCC->AHB1ENR`, `GPIOA->ODR` |
| 02 | led-toggle-struct | Same, using CMSIS struct-based register access for readability | `GPIOA->MODER`, `ODR` |
| 03 | gpio-output | Configuring GPIO output mode properly | `MODER`, `OTYPER`, `OSPEEDR` |
| 04 | gpio-bsrr | Atomic, glitch-free pin set/reset | `GPIOA->BSRR` |
| 05 | uart-tx | UART transmit (polling) | `USART2`, `RCC->APB1ENR` |
| 06 | uart-printf | Retargeting `printf()` over UART | `_write()` syscall, `USART2->DR` |
| 07 | sandbox-experiment | Personal experiment / scratch project | — |
| 08 | uart-modular | Refactoring UART into a reusable multi-file driver | header/source split |
| 09 | uart-rx | UART receive | `USART2->SR (RXNE)`, `DR` |
| 10 | adc-single-conversion | Single analog-to-digital conversion | `ADC1`, `SQR`, `SR (EOC)` |
| 11 | adc-continuous | Continuous / scan-mode ADC sampling | `ADC1->CR2 (CONT)` |
| 12 | systick-delay | Precise blocking delays using the SysTick core timer | `SysTick->LOAD/VAL/CTRL` |
| 13 | timers | General-purpose timer fundamentals | `TIM2`, `PSC`, `ARR`, `CNT` |
| 14 | output-compare | Timer output-compare for waveform / signal generation | `TIM2->CCR`, `CCMR`, `CCER` |
- To be continued
---

## Building a project

Each project builds and flashes from the terminal:

```bash
cd 14-output-compare
make clean
make            # compile + link -> .elf / .bin
make flash      # flash to the board over OpenOCD/SWD
```

---

## Why bare-metal?

I love to understand how things work at the lowest level so I wrote these against the silicon directly without abstraction layers to understand exactly what the hardware is doing: how clocks gate peripherals, how interrupts reach the core, and what every bit in a control register means. The goal is to build firmware intuition that transfers to any MCU, not just to one vendor's libraries.

---

*Part of my path toward embedded / firmware engineering; next up: FreeRTOS and a closed-loop motor controller*