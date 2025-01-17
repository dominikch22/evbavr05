#include <avr/io.h>
#include <util/delay.h>

#include "i2c.h"
#include "rtc.h"

#define DS1307_ADDRESS 0x68

void rtc_init()
{
	i2c_init(); 
	if(i2c_start(0x68) == 2){
		DDRD |= (1 << PD6); 
		PORTD &= ~(1 << PD6);
	};
	//there is an ack between here that we arent checking for
	if(!i2c_write(0x07))
	{
		//DDRD |= (1 << PD6); 
		//PORTD &= ~(1 << PD6);
	}
	i2c_write(0x00);
	i2c_stop();
	_delay_us(1000);
}

void i2c_scan() {
    uint8_t address;
    for(address = 1; address < 127; address++) {
		if(i2c_start(address << 1) == 1){
			DDRD |= (1 << PD6); 
			PORTD &= ~(1 << PD6);
		};
        i2c_stop();
    }
}

void rtc_write(unsigned char address, unsigned char data)
{
	i2c_start(DS1307_ADDRESS << 1);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
	_delay_us(1000);
}

unsigned char rtc_read(unsigned char address)
{
	unsigned char data;
	

	i2c_start(DS1307_ADDRESS << 1);
	
	i2c_write(address);
	i2c_stop();
	_delay_us(1000);

	i2c_start((DS1307_ADDRESS << 1) | 0x01); 

	 //we send a NACK
	i2c_stop();
	
	data = i2c_read(0);


	//add a small delay here
	_delay_us(1000);
	return data;
}

//test this out
void rtc_multiread(unsigned char address, unsigned char* data, unsigned char len)
{
	i2c_start(DS1307_ADDRESS << 1);
	//slave write address
	i2c_write(address);

	_delay_us(1000);

	//repeated start
	i2c_start((DS1307_ADDRESS << 1) | 0x01);
	//slave read address
	while(len > 1)
	{
		*data++ = i2c_read(1); //send ack here
		len--;
	}

	*data++ = i2c_read(0); //send nack here
	i2c_stop();
	//keep reading till len ==0
	_delay_us(1000);
}