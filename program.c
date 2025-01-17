#include "library/rtc/rtc.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

struct tm {
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
};

struct tm rtc_get_time() {
  struct tm current_time;
  current_time.sec = rtc_read(0x00);
  current_time.min = rtc_read(0x01);
  current_time.hour = rtc_read(0x02);

  return current_time;
}

void adc_init() {
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t channel) {
  ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC))
    ;
  return ADC;
}

char time_str[17];

uint8_t display_mode = 0;
char text[] = "Akademia Bialska ";
char clearText[17];
char display[17];
int main(void) {
  DDRD |= (1 << PD6);
  PORTD |= (1 << PD6);
  DDRD &= ~(1 << PD7);
  PORTD |= (1 << PD7);
  // PORTD &= ~(1 << PD7);

  //rtc_init();
  i2c_scan();
  strcpy(display, text);
  adc_init();
  lcd_begin();

  while (1) {

     if(display_mode == 1){
      show_voltage();
    }else{
      show_temp();
    }
    toggle();
    akademia();
    _delay_ms(800);
  }

  return 0;
}

void show_time() {
  struct tm current_time = rtc_get_time();

  sprintf(time_str, "%02d:%02d:%02d", current_time.hour, current_time.min,
          current_time.sec);

  lcd_set_cursor(0, 1);
  lcd_print(time_str);
}

void show_temp() {
  char temp_str[16];
  uint16_t adc_val = adc_read(0);
  uint16_t temp = (adc_val * 500) / 1024;
  sprintf(temp_str, "Temp: %d C", temp);

  lcd_set_cursor(0, 1);
  lcd_print("                "); 
  lcd_set_cursor(0, 1);
  lcd_print(temp_str);
}

void show_voltage() {
 
   char volt_str[17] = {0};
    uint16_t adc_val = adc_read(1);
    float voltage = (adc_val * 5.0f) / 1023.0f;
    
    int whole = (int)voltage;                    
    int decimal = (voltage - whole) * 100;       
    
    sprintf(volt_str, "Volt: %d.%02d V", whole, decimal);
    lcd_set_cursor(0, 1);
    lcd_print("                "); 
    lcd_set_cursor( 0, 1);
    lcd_print(volt_str);
}

void toggle_display() { 
      display_mode = (display_mode + 1) % 2;
  }

static bool was_low = false;
void toggle() {
  static unsigned long last_toggle = 0;
  uint16_t adc_value = adc_read(2);

  if (adc_value < 100 && !was_low) {
    toggle_display();
    was_low = true;
  } else {
    was_low = false;
  }
}

void akademia() {
  lcd_set_cursor(0, 0);
  lcd_print(display);

  char first = display[0];
  for (int j = 0; j < strlen(text) - 1; j++) {
    display[j] = display[j + 1];
  }
  display[strlen(text) - 1] = first;
}