/*
 * QkThings LICENSE
 * The open source framework and modular platform for smart devices.
 * Copyright (C) 2014 <http://qkthings.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qk_peripheral.h"
#include "qk_peripheral_p.h"

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

void _qk_pwm_startup()
{
    // initialize timer0 in PWM mode
    TCCR2A  |= (1<<WGM20)|(1<<COM2A1)|(1<<WGM21);
    TCCR2B  |= (1<<CS22) | (1<<CS20) ;//| (1<<CS21);
  
    // make sure to make OC0 pin (pin PB3 for atmega32) as output pin
    DDRB |= 0xFF;

//	qk_pwm_start();
}
  
void qk_pwm_start()
{
    static uint8_t brightness = 0;
  

	_qk_pwm_startup();
  
    // run forever
//    while(1)
  //  {
        // increasing brightness
       // for (brightness = 0; brightness < 255; ++brightness)
       // {
            // set the brightness as duty cycle
            OCR2A = brightness;
	brightness +=1;  
            // delay so as to make the user "see" the change in brightness
         //   _delay_ms(10);
        //}
  
        // decreasing brightness
 /*       for (brightness = 255; brightness > 0; --brightness)
        {
            // set the brightness as duty cycle
            OCR2A = brightness;
  
            // delay so as to make the user "see" the change in brightness
            _delay_ms(10);
        }
 */ 
    // repeat this forever
 //   }
}



