#include "eeprom.h"

void EEPROM_write_byte(uint16_t address, uint8_t data)
{
    // Czekaj na zakończenie poprzedniego zapisu
    while(EECR & (1<<EEWE));
    
    // Ustaw adres i dane
    EEAR = address;
    EEDR = data;
    
    // Rozpocznij zapis
    EECR |= (1<<EEMWE);
    EECR |= (1<<EEWE);
}

uint8_t EEPROM_read_byte(uint16_t address)
{
    // Czekaj na zakończenie poprzedniego zapisu
    while(EECR & (1<<EEWE));
    
    // Ustaw adres
    EEAR = address;
    
    // Rozpocznij odczyt
    EECR |= (1<<EERE);
    
    return EEDR;
}

void EEPROM_write_uint16(uint16_t address, uint16_t data)
{
    // Zapisz młodszy bajt
    EEPROM_write_byte(address, (uint8_t)(data & 0xFF));
    // Zapisz starszy bajt
    EEPROM_write_byte(address + 1, (uint8_t)(data >> 8));
}

uint16_t EEPROM_read_uint16(uint16_t address)
{
    uint16_t result;
    
    // Odczytaj młodszy bajt
    result = EEPROM_read_byte(address);
    // Odczytaj starszy bajt
    result |= ((uint16_t)EEPROM_read_byte(address + 1)) << 8;
    
    return result;
}