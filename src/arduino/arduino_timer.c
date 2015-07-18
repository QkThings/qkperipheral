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
#include <util/delay.h>
#include <avr/interrupt.h>

#define _TOP      16
#define _PRE      1024
#define _PRE_BITS ((1 << CS12) | (1 << CS10))

ISR(TIMER1_COMPA_vect)
{
	_qk_timer_handle_interrupt(_QK_PROGRAM_TIMER1);
}

void _qk_timer_startup(void)
{
	OCR1A = _TOP * 1000; // ~1s
	TCCR1B |= (1 << WGM12);  // (mode 4)
	TIMSK1 |= (1 << OCIE1A); // Set compare match to TIMER1_COMPA_vect
}

void qk_timer_set_period(qk_timer id, unsigned int value, qk_timer_scale scale)
{
	if(id == _QK_PROGRAM_TIMER1)
	{
		OCR1A = _TOP * value;   //1/fosc * pre * top = 1ms
		TCCR1B |= (1 << WGM12);  // (mode 4)
		TIMSK1 |= (1 << OCIE1A); // Set compare match to TIMER1_COMPA_vect
	}
}

void qk_timer_set_frequency(qk_timer id, unsigned int value)
{
	qk_timer_set_period(id, 1000.0/(float)value, QK_TIMER_SCALE_MSEC);
}

void qk_timer_start(qk_timer id)
{
	if(id == _QK_PROGRAM_TIMER1)
	{
		TCCR1B |= _PRE_BITS;
	}
}

void qk_timer_stop(qk_timer id)
{
	if(id == _QK_PROGRAM_TIMER1)
	{
		TCCR1B &= ~((1 << CS12) | (1 << CS11)  | (1 << CS10));
	}
}


void qk_timer_restart(qk_timer id)
{
	if(id == _QK_PROGRAM_TIMER1)
	{
		TCNT1 = 0;
		TCCR1B |= _PRE_BITS;
	}
}

void delay_ms(uint16_t value)
{
	_delay_ms(value);
}

void delay_us(uint16_t value)
{
	_delay_us(value);
}
