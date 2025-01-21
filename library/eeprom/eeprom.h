#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include <stdint.h>

void EEPROM_write_uint16(uint16_t address, uint16_t data);

uint16_t EEPROM_read_uint16(uint16_t address);

void EEPROM_write_byte(uint16_t address, uint8_t data);
uint8_t EEPROM_read_byte(uint16_t address);

#endif