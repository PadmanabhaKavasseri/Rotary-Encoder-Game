/********************************************
 *
 *  Name:
 *  Email:
 *  Section:
 *  Assignment: Lab 6 - Analog-to-digital conversion
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "lcd.h"
#include "adc.h"



int main(void)
{
    unsigned char adc_result;


    // Initialize the LCD
    lcd_init();


    // Initialize the ADC
    adc_init(5);

    // Use the ADC to find a seed for rand();
    adc_result = adc_sample();
    srand(adc_result << 8 | adc_result);  // Make a 16-bit number for srand()

    // Write splash screen

        lcd_moveto(0,0);
        lcd_stringout("Padmanabha Kavasseri");
        lcd_moveto(1,0);
        lcd_stringout("EE 109 - Lab 6");
        _delay_ms(1000);
        lcd_writecommand(1);


    // Find a random initial position of the 'X'
        int x  = rand() % 16;


    // Display the 'X' on the screen
        lcd_moveto(0,x);
        lcd_stringout("X");

    int xpos;
    int oldxpos;
    int count = 0;
    while (1) {                  
    // Do a conversion
        adc_result = adc_sample();
        oldxpos = xpos;
        xpos = adc_result/16;
       //  char buf [8];
       // itoa (adc_result,buf,2);
       //  lcd_moveto(0,0);
       //  lcd_stringout(buf);

        // break;
	// Move '^' to new position
        if (xpos != oldxpos){
        lcd_moveto(1,oldxpos);
        lcd_stringout(" ");
        lcd_moveto(1,xpos);

        lcd_stringout("^");
    }


	// Delay
        _delay_ms(10);


	// Check if '^' is aligned with 'X'
        if (xpos == x){
            count++;
            if (count == 200){
                lcd_moveto(0,0);
                lcd_stringout("Winner Winner");  
                break;

            }

        }
        else {
            count = 0;
        }


    }

    return 0;   /* never reached */
}

