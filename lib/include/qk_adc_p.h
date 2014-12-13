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

#ifndef QK_ADC_P_H
#define QK_ADC_P_H

typedef struct
{
	uint8_t flags;
} _qk_adc_struct;


extern _qk_adc_struct _qk_adc;

void _qk_adc_startup();
void _qk_adc_init();

void _qk_adc_handle_sampling_done();

void _qk_adc_setup(qk_adc_ch ch);


#endif

