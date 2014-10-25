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


#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

// ADC Interrupt Routine
ISR(ADC_vect)
{
	qk_adc_flag_set(QK_ADC_FLAG_INTERRUPT);
}


void _qk_adc_startup()
{
	// Set reference analog (AREF) to  Vcc (5V) 
	// using the ADC Multiplexer 
	ADMUX = (1<<REFS0);
 	
	// Set general ADC options using the
	// Control and Status Register:
	// Enable ADC
	ADCSRA = (1<<ADEN);
	// Enable ADC interrupt	
    	ADCSRA |= (1<<ADIE);
	// Set ADC Prescaler to 128
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

void _qk_adc_setup(qk_adc_ch ch)
{
	// Select ADC channel
	ADMUX = (ADMUX & 0xF0) | (ch & 0x07);
}

void _qk_adc_start()
{
	// Set Sleep Mode to ADC Noise Reduction
	set_sleep_mode (SLEEP_MODE_ADC);
	// Enable Sleep Mode
	sleep_enable();
   	while( !(qk_adc_flags() & QK_ADC_FLAG_DONE) )
	{
		// Enter Sleep Mode 
    		sleep_cpu();

		//Check if the MCU woke up 
		//due to the ADC interrupt

		qk_mcu_interrupt_disable();
		
		if( qk_adc_flags() & QK_ADC_FLAG_INTERRUPT )
		{
			qk_adc_flag_set(QK_ADC_FLAG_DONE); 
			qk_adc_flag_clear(QK_ADC_FLAG_INTERRUPT);
		}

		qk_mcu_interrupt_enable();
        }
	// After the procedure
	// disable the Sleep Mode
	sleep_disable();
}

uint8_t _qk_adc_done()
{
	if( qk_adc_flags() & QK_ADC_FLAG_DONE )
	{ 
		qk_adc_flag_clear(QK_ADC_FLAG_DONE);
		return 1;
	}
	else	return 0;
}

inline uint16_t _qk_adc_read()
{
	// Read ADC register
	return ADC;
}

