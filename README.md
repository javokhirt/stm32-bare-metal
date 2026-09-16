# STM32F411 bare-metal drivers

Register-level peripheral drivers for the STM32F411RE (Cortex-M4), written from
the reference manual. No HAL, no LL, no CubeMX. Toolchain is `arm-none-eabi-gcc`,
Make, OpenOCD, and GDB over SWD — fully terminal-driven.

This repo started as fifteen numbered lesson folders, written while I was
learning bare-metal from zero. The lessons did their job, so they're gone.
What's left is one copy of each driver, cleaned up and current. The
lesson-by-lesson history is still in git if you want the archaeology.

The I2C driver kept going after this repo. It grew into
[sentinel-node](https://github.com/javokhirt/sentinel-node), got its API
reshaped for a command-driven sensor, and picked up a fix for an ACK race on
the last byte of a read. The fix is backported here; the writeup lives there.

## Drivers

| Module | Peripheral | What it does |
|---|---|---|
| `gpio` | GPIOA/C | board LED and user button, set/reset through BSRR |
| `uart` | USART2 | 115200 8N1 on the ST-Link VCP, `printf()` retargeted via `_write()` |
| `systick` | SysTick | blocking millisecond delay |
| `adc` | ADC1 | single or continuous conversion on PA1 |
| `tim` | TIM2 | 1 Hz timebase, blocking wait on the update flag |
| `i2c` | I2C1 | 100 kHz master, register-address read/write |

Everything runs on the 16 MHz HSI with no clock-tree configuration — one less
thing to get wrong while the point is the peripherals.

## Build and flash

Each driver has one example under `examples/`:

| Example | Shows |
|---|---|
| `blinky` | LED toggled on a SysTick delay |
| `button` | button state to LED, atomic BSRR writes |
| `uart-echo` | echo plus LED control from the terminal |
| `adc-stream` | free-running conversions of PA1 over UART |
| `tim-blink` | LED paced by TIM2 update events |
| `i2c-whoami` | WHO_AM_I read from an MPU6050, or any register-based device |

```sh
make                          # build the default example (blinky)
make EXAMPLE=uart-echo        # build a specific one
make EXAMPLE=uart-echo flash  # flash over OpenOCD/SWD
make examples                 # build every example
make size disasm debug clean  # the usual
```

Needs `arm-none-eabi-gcc` and `openocd`. `blinky` is about 1 KB of flash; the
examples that print pull in newlib's `printf` and land around 34 KB.

For the UART side, `tools/serial_monitor.py` (pyserial) auto-detects the port
and does ascii, hex, and mixed views with optional logging.

## Pins

| Pin | Function |
|---|---|
| PA5 | LED (LD2) |
| PC13 | user button (B1), external pull-up |
| PA2 / PA3 | USART2 TX / RX, routed to the ST-Link VCP |
| PA1 | ADC1 channel 1 |
| PB8 / PB9 | I2C1 SCL / SDA |

## Layout

```
drivers/    one .c/.h pair per peripheral
examples/   one main.c per driver
platform/   startup and linker script
tools/      OpenOCD config, serial monitor
vendor/     CMSIS headers, trimmed to what an F411 build needs
```

## Status

The lesson code all ran on this board. Consolidating it changed three things
that haven't been re-flashed since:

- The TIM2 rate. The lesson set ARR to 2000 on a 1 kHz counter clock and
  called it 1 Hz. That's 0.5 Hz. Now it's 1000, and actually 1 Hz.
- The I2C read tail. Clearing ACK inside a per-byte loop races the byte
  already arriving on the wire; the last three bytes now drain under a
  stretched clock via BTF (RM0383 §18.3.3). This sequence is proven on
  hardware in sentinel-node.
- The GPIO code moved behind a small API instead of raw writes in `main`.

Nothing here is exotic, but "compiles and I believe it is correct" is not the
same as verified.

Known limits, on purpose:

- No timeouts. Every wait loop spins forever if the hardware doesn't respond.
- I2C reads of exactly 2 bytes need the POS bit and a different sequence.
  Guarded out rather than implemented untested.

## Reference documents

- [RM0383](https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) — the reference manual, where all of this comes from
- [STM32F411RE datasheet](https://www.st.com/resource/en/datasheet/stm32f411re.pdf)
- [UM1724](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf) — Nucleo-64 board manual, pin routing
- [Cortex-M4 generic user guide](https://developer.arm.com/documentation/dui0553/latest/)

## Next

New peripherals land here as I need them — SPI and DMA are the obvious gaps,
both waiting on the SX126x radio work. Project firmware lives in
sentinel-node; this repo stays the shelf the drivers come off of.
