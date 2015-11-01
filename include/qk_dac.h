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

/** \addtogroup QkDAC
 * @brief Digital-to-Analog Converter (DAC)
 *  @{
 */

#ifndef QK_DAC_H
#define QK_DAC_H

typed uint32_t qk_dac;

typedef struct qk_dac_ch
{
	qk_dac   dac;
	uint32_t ch;
} qk_dac_ch;

void qk_dac_set_value(qk_dac_ch ch, uint32_t value);
uint32_t qk_dac_get_value(qk_dac_ch ch);

#endif

/** @}*/
