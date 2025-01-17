#ifndef _RTC_H
#define _RTC_H

void i2c_scan();
void rtc_init();
void rtc_write(unsigned char address, unsigned char data);
unsigned char rtc_read(unsigned char address);

//NOTE: MAKE MORE FUNCTIONS LATER ON
//test this
void rtc_multiread(unsigned char address, unsigned char* data, unsigned char len);

#endif