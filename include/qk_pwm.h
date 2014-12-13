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

/** \addtogroup QkPWM
 * @brief Pulse-Width Modulation (PWM)
 *  @{
 */

#ifndef QK_PWM_H
#define QK_PWM_H

/**
 * @brief .
 */
void qk_pwm_start();

/**
 * @brief .
 */
void qk_pwm_stop()

/**
 * @brief .
 */
 
void qk_pwm_set_duty_cycle(uint8_t duty_cycle);

#endif

/** @}*/

