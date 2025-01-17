//atmega16a kompilator avr-as
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

	lcd_begin();
    
	

    lcd_set_cursor(0, 0);
    lcd_print("Akademia Bialska");

    while (1) 
    {
	 
    }

    return 0;  
}
