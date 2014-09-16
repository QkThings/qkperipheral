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

/** \addtogroup QkTimer
 * @brief Timers
 *  @{
 */

#ifndef QK_TIMER_H
#define QK_TIMER_H

/**
 * Timer ID
 */
typedef enum
{
	_QK_PROGRAM_TIMER0,
	_QK_PROGRAM_TIMER1,
	QK_TIMER_0,
	QK_TIMER_1,
	QK_TIMER_2,
	QK_TIMER_3,
	QK_TIMER_4,
	QK_TIMER_5,
} qk_timer;


/**
 * Timer Scale
 */
typedef enum
{
	QK_TIMER_SCALE_USEC,//!< QK_TIMER_SCALE_USEC
	QK_TIMER_SCALE_MSEC,//!< QK_TIMER_SCALE_MSEC
	QK_TIMER_SCALE_SEC //!< QK_TIMER_SCALE_SEC
} qk_timer_scale;

typedef enum
{
	QK_TIMER_FLAG_TIMEOUT = (1<<0),
	QK_TIMER_FLAG_OVERLAP = (1<<1)
} qk_timer_flag;

/**
 * @brief .
 */
int qk_timer_set_period(qk_timer id, unsigned int value, qk_timer_scale scale);

/**
 * @brief .
 */
int qk_timer_set_frequency(qk_timer id, unsigned int value);


/**
 * @brief .
 */
void qk_timer_start(qk_timer id);

/**
 * @brief .
 */
void qk_timer_stop(qk_timer id);

/**
 * @brief .
 */
void qk_timer_restart(qk_timer id);


uint32_t qk_timer_flags(qk_timer id);
void qk_timer_flags_clear(qk_timer id, uint32_t flags);


void delay_us(uint16_t value);
void delay_ms(uint16_t value);
void delay_s(uint16_t value);

#endif // QK_TIMER_H

/** @}*/

