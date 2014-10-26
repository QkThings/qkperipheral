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

#ifndef QK_PWM_P_H
#define QK_PWM_P_H

typedef struct
{
	uint8_t flags;
} _qk_pwm_struct;


extern _qk_pwm_struct _qk_pwm;

void _qk_pwm_startup();
void _qk_pwm_init();

void _qk_pwm_setup(qk_pwm_ch ch);
void _qk_pwm_start();
void qk_pwm_start();
uint8_t _qk_pwm_done();
uint16_t _qk_pwm_read();


#endif

