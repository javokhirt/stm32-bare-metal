# Serial Monitor

A small Python serial monitor for watching UART traffic from the STM32 on macOS.

## Hardware wiring

Your firmware transmits on **USART2 TX = PA2** at **115200 8-N-1**. To capture
this on the Mac, use a 3.3 V USB-to-serial adapter (FTDI / CP2102 / CH340):

| STM32          | USB-Serial adapter |
|----------------|--------------------|
| `PA2` (TX)     | `RX`               |
| `GND`          | `GND`              |

Do **not** connect the adapter's 3.3 V/5 V to the board if the board is already
powered, and never connect TX↔TX.

> Tip: Nucleo boards expose USART2 over the on-board ST-LINK as a Virtual COM
> Port. If you're using a Nucleo, just plug in the ST-LINK USB and you don't
> need a separate adapter — the port will appear as `/dev/cu.usbmodem*`.

## Setup

```bash
cd 05-uart-tx/Tools
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

## Usage

```bash
# Auto-detect port at 115200 baud
python3 serial_monitor.py

# Explicit port
python3 serial_monitor.py -p /dev/cu.usbserial-XYZ -b 115200

# List available ports
python3 serial_monitor.py --list

# Hex + ASCII view with timestamps
python3 serial_monitor.py --mode mixed -t

# Save the raw stream to a file as well
python3 serial_monitor.py --log capture.bin
```

Press `Ctrl+C` to quit.

## Built-in alternative (no Python)

macOS already ships with `screen`:

```bash
screen /dev/cu.usbserial-XYZ 115200
```

Exit with `Ctrl+A` then `K`, then `y`.
