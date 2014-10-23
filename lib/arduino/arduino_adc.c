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

// ADC Interrupt is only used to wake up CPU from Sleep Mode
EMPTY_INTERRUPT (ADC_vect);

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

int qk_adc_read(qk_adc_ch ch)
{
	// Select ADC channel
	ADMUX = (ADMUX & 0xF0) | (ch & 0x07);
	// Set Sleep Mode to ADC Noise Reduction
	set_sleep_mode (SLEEP_MODE_ADC);
	// Enable Sleep Mode
	sleep_enable();
   	// Enter Sleep Mode 
    	sleep_cpu();
	// After waking up, disable the Sleep Mode
	sleep_disable();
        // Return the ADC 10-bit word 
        return ADC;
}

