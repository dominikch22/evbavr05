#!/bin/bash

LIBRARY_PATH="library"

MAIN_PROGRAM="program.c"

OUTPUT="program"

AVR_GCC_FLAGS="-mmcu=atmega16a -Os -Wall"


LIBRARY_SOURCES=$(find "$LIBRARY_PATH" -type f \( -name "*.c" -o -name "*.h" \))

avr-gcc $AVR_GCC_FLAGS $LIBRARY_SOURCES $MAIN_PROGRAM -o "$OUTPUT.elf"

avr-objcopy -O ihex -R .eeprom "$OUTPUT.elf" "$OUTPUT.hex"

sudo avrdude -c usbasp -p m16 -P usb -U flash:w:program.hex
