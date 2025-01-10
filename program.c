#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

	lcd_begin();
    
	char text[] = "Akademia Bialska   ";
    char clearText[17];
    int length = strlen(text);
    char display[17];

    while (1) 
    {
	 strcpy(display, text);
        
        for(uint8_t i = 0; i < length; i++) 
        {
            lcd_write_byte(0x01, 0); 
            _delay_ms(150);


            lcd_set_cursor(0, 0);
            lcd_print(display);
            _delay_ms(200);
            
            char first = display[0]; 
            for(int j = 0; j < length-1; j++) {
                display[j] = display[j+1];
            }
            display[length-1] = first;
        }
    }

    return 0;  
}
