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

_qk_adc_struct _qk_adc;

void _qk_adc_init()
{
	memset(&_qk_adc, 0, sizeof(_qk_adc_struct));
}

uint8_t qk_adc_flags()
{
	return _qk_adc.flags;
}

void qk_adc_flags_clear()
{
	_qk_adc.flags = 0;
}

void qk_adc_flag_clear(qk_adc_flag flag)
{	
	_qk_adc.flags &= ~flag;
}

void qk_adc_flag_set(qk_adc_flag flag)
{
	_qk_adc.flags |= flag;
}

uint16_t qk_adc_read(qk_adc_ch ch)
{
	// Setup the ADC
	_qk_adc_setup(ch);
	// Start conversion
	_qk_adc_start();
	// Wait for the ADC
	while(!_qk_adc_done());
	// Return the ADC result
	return _qk_adc_read();
}
