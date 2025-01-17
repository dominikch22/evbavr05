﻿/*
 * lcd.h
 *
 * Created: 2/20/2020 1:17:15 AM
 *  Author: Shuvangkar
 */ 


#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000UL

#include <avr/io.h>
#include "util/delay.h"

/**************************************/
/*			 LCD Connection           */
/**************************************/
#define RS_PORT		PORTD
#define RS_PIN		PD0

#define RW_PORT		PORTD
#define RW_PIN		PD7

#define EN_PORT		PORTD
#define EN_PIN		PD1

#define D4_PORT		PORTD
#define D4_PIN		PD2

#define D5_PORT		PORTD
#define D5_PIN		PD3

#define D6_PORT		PORTD
#define D6_PIN		PD4

#define D7_PORT		PORTD
#define D7_PIN		PD5

/**************************************/
/*	 LCD Library Internal Functions	  */
/**************************************/
void lcd_port_init_4Bit();
void map_data_port(unsigned char data);
void lcd_write_nibble(unsigned char data, uint8_t type); //type->0= cmd, type
void lcd_write_cmd_with_delay(unsigned char data);
void lcd_write_byte(unsigned char data, uint8_t type);
void lcd_busy_wait();

/**************************************/
/*			 LCD Public Functions	  */
/**************************************/

void lcd_begin();
void lcd_set_cursor(char x,char y);
void lcd_print(char* str);

/**************************************/
/*			 COMMON MACRO		     */
/**************************************/
#define DDR(port)  (*(&port-1))
#define PIN(port) (*(&port - 2)) 

#define setBit(port, bit) (port) |= (1 << (bit))
#define clearBit(port, bit) (port) &= ~(1 << (bit))

#define WRITE_PIN(PORT,PIN,STATE) ((PORT) = ((PORT&(~(1<<PIN)))|(STATE<<PIN)))

/**************************************/
/*			 Utility MACRO	          */
/**************************************/
#define RS_HI() setBit(RS_PORT,RS_PIN)
#define RS_LO() clearBit(RS_PORT,RS_PIN)

#define RW_HI() setBit(RW_PORT,RW_PIN)
#define RW_LO() clearBit(RW_PORT,RW_PIN)

#define EN_HI() setBit(EN_PORT,EN_PIN)
#define EN_LO() clearBit(EN_PORT,EN_PIN)


#define MAP_BIT(value,pos,port,pin)  (port) = (port&(~(1<<pin)))|(((value>>pos)&&1)<<pin)

#define CMD 0
#define DATA 1
#endif /* LCD_H_ */

/*
#define DATA(value)

D4_PORT |= 1<<D4_PIN
value = 0b0000 0111

PORTB = 0b1011 0010
bit0  = 0b1110 1111
--------------------
		0b101

bit0 = (value>>0)&1
bit1 = (value>>1)&1
bit2 = (value>>2)&1
bit3 = (value>>3)&1

D4_PORT = (D4_PORT&(~(1<<D4_PIN)))|(bit0<<D4_PIN);
*/
