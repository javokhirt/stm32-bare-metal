# STM32F411RE bare-metal drivers — builds one example against the full driver set.
#
#   make                        build the default example
#   make EXAMPLE=uart-echo      build a specific example
#   make EXAMPLE=blinky flash   flash it over OpenOCD/SWD
#   make examples               build every example

EXAMPLE  ?= blinky
BUILD_DIR = build/$(EXAMPLE)
EXAMPLES  = $(notdir $(wildcard examples/*))

C_SOURCES   = $(wildcard drivers/*.c) examples/$(EXAMPLE)/main.c
ASM_SOURCES = platform/startup_stm32f411retx.s
LDSCRIPT    = platform/stm32f411retx_flash.ld

# Toolchain
PREFIX  = arm-none-eabi-
CC      = $(PREFIX)gcc
AS      = $(PREFIX)gcc -x assembler-with-cpp
LD      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump
SIZE    = $(PREFIX)size
GDB     = $(PREFIX)gdb

MCU = -mcpu=cortex-m4 -mthumb -mfloat-abi=soft

CFLAGS  = $(MCU)
CFLAGS += -std=c11
CFLAGS += -Wall -Wextra -Wpedantic -Wshadow
CFLAGS += -Wdouble-promotion -Wformat=2 -Wformat-truncation
CFLAGS += -fno-common -ffunction-sections -fdata-sections
CFLAGS += -Os
CFLAGS += -g3 -gdwarf-2
CFLAGS += -I drivers
CFLAGS += -I vendor/CMSIS/Include
CFLAGS += -I vendor/CMSIS/Device/ST/STM32F4xx/Include
CFLAGS += -DSTM32F411xE

ASFLAGS = $(MCU) -g3 -gdwarf-2

LDFLAGS  = $(MCU)
LDFLAGS += -T $(LDSCRIPT)
LDFLAGS += --specs=nosys.specs
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(EXAMPLE).map,--cref
LDFLAGS += -lnosys

OBJECTS  = $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCES:.c=.o)))
OBJECTS += $(addprefix $(BUILD_DIR)/, $(notdir $(ASM_SOURCES:.s=.o)))

vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

.PHONY: all examples clean flash openocd debug size disasm

all: $(BUILD_DIR)/$(EXAMPLE).bin $(BUILD_DIR)/$(EXAMPLE).hex
	@echo "=== $(EXAMPLE) ==="
	@$(SIZE) $(BUILD_DIR)/$(EXAMPLE).elf

examples:
	@for e in $(EXAMPLES); do $(MAKE) --no-print-directory EXAMPLE=$$e || exit 1; done

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "CC  $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	@echo "AS  $<"
	@$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/$(EXAMPLE).elf: $(OBJECTS)
	@echo "LD  $@"
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/$(EXAMPLE).bin: $(BUILD_DIR)/$(EXAMPLE).elf
	@$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/$(EXAMPLE).hex: $(BUILD_DIR)/$(EXAMPLE).elf
	@$(OBJCOPY) -O ihex $< $@

$(BUILD_DIR):
	@mkdir -p $@

# Flash base on STM32F4 = 0x08000000 (linker script, RM0383 §3.3)
flash: $(BUILD_DIR)/$(EXAMPLE).bin
	openocd -f tools/openocd.cfg -c "program $< 0x08000000 verify reset exit"

openocd:
	openocd -f tools/openocd.cfg

debug: $(BUILD_DIR)/$(EXAMPLE).elf
	$(GDB) -ex "target remote :3333" \
	       -ex "monitor reset halt" \
	       -ex "break main" \
	       -ex "continue" \
	       $<

size: $(BUILD_DIR)/$(EXAMPLE).elf
	$(SIZE) --format=berkeley $<

disasm: $(BUILD_DIR)/$(EXAMPLE).elf
	$(OBJDUMP) -d -S $< > $(BUILD_DIR)/$(EXAMPLE).dis
	@echo "-> $(BUILD_DIR)/$(EXAMPLE).dis"

clean:
	rm -rf build
