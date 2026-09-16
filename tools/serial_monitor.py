#!/usr/bin/env python3
"""
Serial Monitor for STM32 UART projects.

Listens on a serial port and prints incoming bytes to the terminal.
Supports plain-text, hex, and mixed views, with optional timestamps.

Examples
--------
    # Auto-detect the first USB-serial port at 115200 baud
    python3 serial_monitor.py

    # Specify a port and baud rate
    python3 serial_monitor.py -p /dev/cu.usbserial-XYZ -b 115200

    # Show hex alongside ASCII, with timestamps
    python3 serial_monitor.py --hex --timestamp

    # Log everything to a file as well
    python3 serial_monitor.py --log capture.txt
"""

from __future__ import annotations

import argparse
import sys
import time
from datetime import datetime

try:
    import serial
    from serial.tools import list_ports
except ImportError:
    sys.stderr.write(
        "Missing dependency 'pyserial'. Install it with:\n"
        "    pip3 install pyserial\n"
    )
    sys.exit(1)


USB_SERIAL_HINTS = (
    "usbserial",
    "usbmodem",
    "SLAB_USBtoUART",
    "wchusbserial",
    "FTDI",
    "CP210",
    "CH340",
)


def find_default_port() -> str | None:
    """Pick the most likely USB-to-serial device, skipping Bluetooth/AirPods."""
    ports = list_ports.comports()
    for p in ports:
        name = p.device.lower()
        if "bluetooth" in name or "airpods" in name or "debug-console" in name:
            continue
        return p.device
    for p in ports:
        if any(hint.lower() in p.device.lower() for hint in USB_SERIAL_HINTS):
            return p.device
    return None


def list_available_ports() -> None:
    ports = list(list_ports.comports())
    if not ports:
        print("No serial ports detected.")
        return
    print("Available serial ports:")
    for p in ports:
        desc = f"  {p.device}"
        if p.description and p.description != "n/a":
            desc += f"    [{p.description}]"
        if p.manufacturer:
            desc += f"    ({p.manufacturer})"
        print(desc)


def format_line(
    data: bytes,
    *,
    show_hex: bool,
    show_ascii: bool,
    timestamp: bool,
) -> str:
    parts: list[str] = []
    if timestamp:
        parts.append(datetime.now().strftime("[%H:%M:%S.%f")[:-3] + "]")
    if show_hex:
        parts.append(" ".join(f"{b:02X}" for b in data))
    if show_ascii:
        ascii_repr = "".join(chr(b) if 32 <= b < 127 else "." for b in data)
        parts.append(ascii_repr)
    return " ".join(parts)


def run_monitor(args: argparse.Namespace) -> int:
    port = args.port or find_default_port()
    if not port:
        print("Could not auto-detect a serial port. Plug in your USB-to-serial "
              "adapter, or pick one of these:")
        list_available_ports()
        return 1

    try:
        ser = serial.Serial(
            port=port,
            baudrate=args.baud,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=0.1,
        )
    except serial.SerialException as exc:
        print(f"Failed to open {port}: {exc}")
        return 1

    show_hex = args.hex or args.mode == "hex"
    show_ascii = (not args.hex) or args.mode in ("ascii", "mixed")
    if args.mode == "mixed":
        show_hex = True
        show_ascii = True

    print(f"Connected to {port} @ {args.baud} baud "
          f"(8-N-1). Press Ctrl+C to exit.\n")

    log_file = open(args.log, "ab") if args.log else None
    line_mode = not (show_hex and not show_ascii)
    buffer = bytearray()

    try:
        while True:
            chunk = ser.read(256)
            if not chunk:
                if line_mode and buffer:
                    pass
                continue

            if log_file:
                log_file.write(chunk)
                log_file.flush()

            if show_hex and not show_ascii:
                print(format_line(chunk, show_hex=True, show_ascii=False,
                                  timestamp=args.timestamp), flush=True)
                continue

            buffer.extend(chunk)
            while b"\n" in buffer:
                line, _, rest = buffer.partition(b"\n")
                buffer = bytearray(rest)
                line = line.rstrip(b"\r")
                print(format_line(bytes(line), show_hex=show_hex,
                                  show_ascii=show_ascii,
                                  timestamp=args.timestamp), flush=True)

            if buffer and not args.line_buffered:
                print(format_line(bytes(buffer), show_hex=show_hex,
                                  show_ascii=show_ascii,
                                  timestamp=args.timestamp), end="", flush=True)
                buffer.clear()

    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        ser.close()
        if log_file:
            log_file.close()
    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Lightweight serial monitor for STM32 UART projects.",
    )
    parser.add_argument("-p", "--port",
                        help="Serial port (e.g. /dev/cu.usbserial-XYZ). "
                             "Auto-detected if omitted.")
    parser.add_argument("-b", "--baud", type=int, default=115200,
                        help="Baud rate (default: 115200).")
    parser.add_argument("--hex", action="store_true",
                        help="Show incoming bytes as hex only.")
    parser.add_argument("--mode", choices=("ascii", "hex", "mixed"),
                        default="ascii",
                        help="Display mode (default: ascii).")
    parser.add_argument("-t", "--timestamp", action="store_true",
                        help="Prefix each line with a timestamp.")
    parser.add_argument("--log",
                        help="Append raw bytes to this file as well.")
    parser.add_argument("--list", action="store_true",
                        help="List available serial ports and exit.")
    parser.add_argument("--line-buffered", action="store_true",
                        help="Only print whole lines (wait for newline).")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.list:
        list_available_ports()
        return 0
    return run_monitor(args)


if __name__ == "__main__":
    sys.exit(main())
