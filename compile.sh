avr-gcc -mmcu=atmega16 -Os -I. -c program.c -o program.o
avr-gcc -mmcu=atmega16 -Os -I. -c lcd_lib.c -o lcd_lib.o
avr-gcc -mmcu=atmega16 -Os -o program.elf program.o lcd_lib.o
avr-objcopy -O ihex -R .eeprom program.elf program.hex
sudo avrdude -c usbasp -p m16 -P usb -U flash:w:program.hex