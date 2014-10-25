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

/** \addtogroup QkADC
 * @brief Analog-to-Digital Coverter (ADC)
 *  @{
 */

#ifndef QK_ADC_H
#define QK_ADC_H

typedef uint32_t qk_adc_ch;

typedef enum{
	QK_ADC_FLAG_INTERRUPT = (1<<0),
	QK_ADC_FLAG_DONE = (1<<1)
} qk_adc_flag;

/**
 * @brief .
 */
uint16_t qk_adc_read(qk_adc_ch ch);

/**
 * @brief .
 */
uint8_t qk_adc_flags();

/**
 * @brief .
 */
void qk_adc_flags_clear();

/**
 * @brief .
 */
void qk_adc_flag_clear(uint8_t flag);

/**
 * @brief .
 */
void qk_adc_flag_set(uint8_t flag);

#endif

/** @}*/

