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

#ifndef QK_GPIO_P_H
#define QK_GPIO_P_H

typedef struct
{
	uint32_t flags;
} _qk_gpio_struct;


#define _QK_GPIO_PORT(pin)	((pin >> 16) & 0xFFFF)
#define _QK_GPIO_BIT(pin)	(pin & 0xFFFF)

extern _qk_gpio_struct _qk_gpio;

void _qk_gpio_init(void);
void _qk_gpio_startup(void);
void _qk_gpio_handle_input_changed();

#endif

