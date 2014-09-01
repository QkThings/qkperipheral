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

/**
 * Timer ID
 */
typedef enum qk_timer
{
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
typedef enum qk_timer_scale
{
	QK_TIMER_SCALE_USEC,//!< QK_TIMER_SCALE_USEC
	QK_TIMER_SCALE_MSEC,//!< QK_TIMER_SCALE_MSEC
	QK_TIMER_SCALE_SEC //!< QK_TIMER_SCALE_SEC
} qk_timer_scale;

/**
 * @brief .
 */
int qk_timer_set_period(qk_timer timer, qk_timer_scale scale, unsigned int value);

/**
 * @brief .
 */
int qk_timer_get_value(qk_timer timer);

/**
 * @brief .
 */
void qk_timer_start(qk_timer timer);

/**
 * @brief .
 */
void qk_timer_stop(qk_timer timer);

/**
 * @brief .
 */
void qk_timer_restart(qk_timer timer);

/**
 * @brief .
 */
void qk_timer_set_interrupt(qk_timer timer, qk_timer_interrupt isr, void (*cb)(void));

/** @}*/

#endif

