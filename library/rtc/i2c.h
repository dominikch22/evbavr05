#ifndef _I2C_H
#define _I2C_H
#include <stdint.h>

void i2c_init();

uint8_t i2c_start(char write_address);
void i2c_stop();

int i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char ack);

#endif