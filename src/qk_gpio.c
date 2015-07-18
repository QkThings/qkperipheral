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

_qk_gpio_struct _qk_gpio;

void _qk_gpio_init()
{
	memset(&_qk_gpio, 0, sizeof(_qk_gpio_struct));
}

void _qk_gpio_handle_input_changed(uint32_t flags)
{
	_qk_gpio.flags |= flags;
}

uint32_t qk_gpio_flags()
{
	return _qk_gpio.flags;
}
void qk_gpio_flags_clear()
{
	_qk_gpio.flags = 0;
}
