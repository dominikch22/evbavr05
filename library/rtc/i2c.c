#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "i2c.h"
#define F_CPU 16000000UL 
#define SCL_CLOCK 100000L 
#define I2C_SDA PC1
#define I2C_SCL PC0

void i2c_init()
{

	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
  TWSR = 0;
	//IF TWSR IS ENABLED CHANGE TWBR TO 2;
	//TWSR |= ((1 << TWPS1) | (0 << TWPS0)); //16 + 2*4^2 //we can change the timing, check
	//Enable the TWI MODULE
  //  DDRC &= ~((1 << I2C_SDA) | (1 << I2C_SCL)); 
  //  PORTC |= (1 << I2C_SDA) | (1 << I2C_SCL);
	TWCR |= (1 << TWEN);
}

uint8_t i2c_start(char write_address) 
{
    uint8_t status;		
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); 
    while (!(TWCR & (1 << TWINT)));	
    status = TWSR & 0xF8;	
    if (status != 0x08)	
        return 0;		
    
    TWDR = write_address;		
    TWCR = (1 << TWEN) | (1 << TWINT);	
    while (!(TWCR & (1 << TWINT)));	
    status = TWSR & 0xF8;	

    if (status == 0x18)		
        return 1;		
    
    if (status == 0x20)		
        return 2;		

    return 3;			
}

void i2c_stop()
{
	//Put Stop Condition on bus
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	
	//while(TWCR & (1<<TWSTO));
}

int i2c_write(unsigned char data)
{
	TWDR=data;	

	//Initiate Transfer
  TWCR = (1<<TWINT) | (1<<TWEN);

	//Poll Till Done
	while(!(TWCR & (1<<TWINT)));
	

	if((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == 0x28 || (TWSR & 0xF8) == 0x40 || (TWSR & 0xF8) == 0x20)
	{
		return 1;
	}
	else{ 
    return 0;	
  }
}

unsigned char i2c_read(unsigned char ack)
{
	//Now enable Reception of data by clearing TWINT
	TWCR =((1<<TWINT) | (1 << TWEN) | (ack << TWEA));

  while(!(TWCR & (1 << TWINT)));

  return TWDR;
}